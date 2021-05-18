#include "stdafx.h"

#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <exception> 

#include "SFTPConnection.h"

namespace systelab { namespace sftp {

	namespace
	{
		// Used by function "sftp_open", parameter mode_t "mode"
		// The mode_t accepted values are defined when #include <sys/types.h> but only for Linux (e.g.: S_IRWXU)
		const mode_t DEFAULT_FILE_PERMISSION = 0; 

		const unsigned int MAX_FILE_READ_BUFFER = 1024;

		struct sshKeyPtr
		{
			~sshKeyPtr() { ssh_key_free(sshKey); };
			ssh_key sshKey = nullptr;
		};

		struct hashPtr
		{
			~hashPtr() { ssh_clean_pubkey_hash(&hash); };
			unsigned char *hash = nullptr;
		};

		struct hexHashPtr
		{
			~hexHashPtr() { ssh_string_free_char(hexHash); };
			char *hexHash = nullptr;
		};
	}

	SFTPConnection::~SFTPConnection()
	{
		close();
	}

	void SFTPConnection::connect(const std::string& ip,
									unsigned int port,
									const std::string& username,
									const std::string& pubKey,
									const std::string& privKey,
									const std::function<std::string()>& getPrivKeyPassPhraseFn,
									const std::vector<std::string>& serverFingerPrints)
	{
		try
		{
			sshConnect(ip, port);
			verifySFTPServerIdentity(serverFingerPrints);
			sshAuthorize(username, pubKey, privKey, getPrivKeyPassPhraseFn());
			sftpConnect();
		}
		catch (const Exception&)
		{
			close();
			throw;
		}
	}

	void SFTPConnection::sshConnect(const std::string& ip, unsigned int port)
	{
		m_sshSession = ssh_new();
		if (!m_sshSession)
		{
			throw SSHSessionCannotCreateException();
		}

		ssh_options_set(m_sshSession, SSH_OPTIONS_HOST, ip.c_str());
		ssh_options_set(m_sshSession, SSH_OPTIONS_PORT, &port);

		if (ssh_connect(m_sshSession) != SSH_OK)
		{
			throw ConectionFailedException(ssh_get_error(m_sshSession));
		}
	}



	void SFTPConnection::sshAuthorize(const std::string& username, const std::string& pubKey,
									  const std::string& privKey, const std::string& privKeyPassPhrase)
	{
		sshKeyPtr publickey;
		sshKeyPtr privatekey;

		if (ssh_pki_import_pubkey_base64(pubKey.c_str(), SSH_KEYTYPE_RSA, &publickey.sshKey) != SSH_OK)
		{
			throw InvalidPublicKeyException();
		}

		if (ssh_userauth_try_publickey(m_sshSession, username.c_str(), publickey.sshKey) != SSH_AUTH_SUCCESS)
		{
			throw AuthenticationFailedException(ssh_get_error(m_sshSession));
		}

		if (ssh_pki_import_privkey_base64(privKey.c_str(), privKeyPassPhrase.c_str(), NULL, NULL, &privatekey.sshKey) != SSH_OK)
		{
			throw InvalidPrivateKeyException();
		}

		if (ssh_userauth_publickey(m_sshSession, username.c_str(), privatekey.sshKey) != SSH_AUTH_SUCCESS)
		{
			throw AuthenticationFailedPrivateException(ssh_get_error(m_sshSession));
		}
	}

	void SFTPConnection::verifySFTPServerIdentity(const std::vector<std::string>& serverFingerPrints)
	{
		sshKeyPtr srv_pubkey;
		hashPtr hash_ptr;
		hexHashPtr hexHash_ptr;

		if (ssh_get_server_publickey(m_sshSession, &srv_pubkey.sshKey) != SSH_OK)
		{
			throw InvalidServerPublicKeyException();
		}
			
		size_t hlen;
		if (ssh_get_publickey_hash(srv_pubkey.sshKey, SSH_PUBLICKEY_HASH_SHA256, &hash_ptr.hash, &hlen) != SSH_OK)
		{
			throw InvalidServerPublicKeyException();
		}  

		hexHash_ptr.hexHash = ssh_get_hexa(hash_ptr.hash, hlen);
		if (std::find(serverFingerPrints.begin(), serverFingerPrints.end(), hexHash_ptr.hexHash) == serverFingerPrints.end())
		{
			throw ServerFingerPrintNotAcceptedException(hexHash_ptr.hexHash);
		}
	}


	void SFTPConnection::sftpConnect()
	{
		m_sftpSession = sftp_new(m_sshSession);
		if (!m_sftpSession)
		{
			throw SFTPSessionCannotCreateException();
		}

		if (sftp_init(m_sftpSession) != SSH_OK)
		{
			throw SFTPSessionCannotInitException(ssh_get_error(m_sshSession));
		}
	}


	bool SFTPConnection::isConnected() const
	{
		return m_sftpSession;
	}


	void SFTPConnection::upload(const std::string& srcFile, const std::string& dstFile)
	{
		if (!isConnected())
		{
			throw InvalidConnectionException();
		}

		// create the destination file in the server
		sftp_file serverFile = sftp_open(m_sftpSession, dstFile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, DEFAULT_FILE_PERMISSION);
		if (!serverFile)
		{
			throw SFTPCannotCreateRemoteFileException(ssh_get_error(m_sshSession));
		}


		char buffer[MAX_FILE_READ_BUFFER];
		std::ifstream file(srcFile, std::ios::binary);
		while (file)
		{
			file.read(buffer, sizeof(buffer));  // read the source file content
			if (file.gcount() > 0)
			{
				size_t nwritten = sftp_write(serverFile, buffer, (size_t) file.gcount()); // upload the content on the server
				if (nwritten != file.gcount())
				{
					throw SFTPCannotWriteRemoteFileException(ssh_get_error(m_sshSession));
				}
			}
			else
			{
				throw SFTPCannotReadLocalFileException(ssh_get_error(m_sshSession));
			}
		}

		sftp_close(serverFile);
	}

	void SFTPConnection::rename(const std::string& srcFile, const std::string& dstFile)
	{
		if (!isConnected())
		{
			throw InvalidConnectionException();
		}

		if (sftp_rename(m_sftpSession, srcFile.c_str(), dstFile.c_str()) != SSH_OK)
		{
			throw SFTPCannotRenameRemoteFileException(ssh_get_error(m_sshSession));
		}
	}

	void SFTPConnection::close()
	{
		if (m_sftpSession)
		{
			sftp_free(m_sftpSession);
			m_sftpSession = nullptr;
		}

		if (m_sshSession)
		{
			ssh_disconnect(m_sshSession);
			ssh_free(m_sshSession);
			m_sshSession = nullptr;
		}
	}

}}