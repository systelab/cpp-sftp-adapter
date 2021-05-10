#include "stdafx.h"

#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "SFTPConnection.h"

namespace systelab { namespace sftp {


		SFTPConnection::SFTPConnection()
		{
			m_sshSession = nullptr;
			m_sftpSession = nullptr;
		}

		SFTPConnection::~SFTPConnection()
		{
			close();
		}

		void SFTPConnection::connect(const std::string& ip,
									 unsigned int port,
									 const std::string& username,
									 const std::string& pubKeyFile,
									 const std::string& privKeyFile,
									 std::function<std::string()> getPrivKeyPassPhraseFn,
									 const std::vector<std::string>& serverFingerPrints)
		{
			if (sshConnect(ip, port))
			{
				if (verifySFTPServerIdentity(serverFingerPrints))
				{
					if (sshAuthorize(username, pubKeyFile, privKeyFile, getPrivKeyPassPhraseFn()))
					{
						if (sftpConnect())
						{
							return; // connected
						}
					}
				}
			}

			close();
		}


		std::string readFileContent(const std::string filename)
		{
			std::string content = "";
			try
			{
				std::ifstream file(filename);

				file.seekg(0, std::ios::end);
				content.reserve((unsigned int)file.tellg());
				file.seekg(0, std::ios::beg);

				content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			}
			catch (...) {}
			return content;
		}



		bool SFTPConnection::sshConnect(const std::string& ip, unsigned int port)
		{
			m_sshSession = ssh_new();
			if (m_sshSession == nullptr)
			{
				return false;
			}

			ssh_options_set(m_sshSession, SSH_OPTIONS_HOST, ip.c_str());
			ssh_options_set(m_sshSession, SSH_OPTIONS_PORT, &port);

			if (ssh_connect(m_sshSession) != SSH_OK)
			{
				return false;
			}

			return true;
		}

		bool SFTPConnection::sshAuthorize(const std::string& username, const std::string& pubKeyFile,
			const std::string& privKeyFile, const std::string& privKeyPassPhrase)
		{
			bool authorized = false;
			ssh_key publickey = nullptr;
			ssh_key privatekey = nullptr;

			// IMPORTANT only base64 format public key are accepted as file content
			std::string publicKeyFileContent = readFileContent(pubKeyFile);
			if (ssh_pki_import_pubkey_base64(publicKeyFileContent.c_str(), SSH_KEYTYPE_RSA, &publickey) == SSH_OK)
			{
				if (ssh_userauth_try_publickey(m_sshSession, username.c_str(), publickey) == SSH_OK)
				{
					// IMPORTANT only openSSH format private key file are accepted
					if (ssh_pki_import_privkey_file(privKeyFile.c_str(), privKeyPassPhrase.c_str(), NULL, NULL, &privatekey) == SSH_OK)
					{
						authorized = ssh_userauth_publickey(m_sshSession, username.c_str(), privatekey) == SSH_OK;
					}
				}
			}

			ssh_key_free(publickey);
			ssh_key_free(privatekey);

			return authorized;
		}

		bool SFTPConnection::verifySFTPServerIdentity(const std::vector<std::string>& serverFingerPrints)
		{
			ssh_key srv_pubkey = nullptr;
			if (ssh_get_server_publickey(m_sshSession, &srv_pubkey) != SSH_OK)
			{
				return false;
			}

			unsigned char *hash = nullptr;
			size_t hlen;
			int rc = ssh_get_publickey_hash(srv_pubkey, SSH_PUBLICKEY_HASH_SHA256, &hash, &hlen);
			ssh_key_free(srv_pubkey);
			if (rc != SSH_OK)
			{
				return false;
			}

			char *hexHash = ssh_get_hexa(hash, hlen);
			bool foundServer = std::find(serverFingerPrints.begin(), serverFingerPrints.end(), hexHash) != serverFingerPrints.end();
			ssh_string_free_char(hexHash);
			ssh_clean_pubkey_hash(&hash);

			return foundServer;
		}


		bool SFTPConnection::sftpConnect()
		{
			m_sftpSession = sftp_new(m_sshSession);
			if (m_sftpSession == nullptr)
			{
				return false;
			}

			if (sftp_init(m_sftpSession) != SSH_OK)
			{
				return false;
			}

			return true;
		}


		bool SFTPConnection::isConnected() const
		{
			return m_sftpSession != nullptr;
		}


		bool SFTPConnection::upload(const std::string& srcFile, const std::string& dstFile)
		{
			if (!isConnected())
			{
				return false;
			}

			// create the destination file in the server
			sftp_file serverFile = sftp_open(m_sftpSession, dstFile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0);
			if (serverFile == nullptr)
			{
				return false;
			}

			// read the source file content
			std::string contentClientFile = readFileContent(srcFile);
			if (contentClientFile.empty())
			{
				return false;
			}

			// upload the content ot the server
			int nWritten = sftp_write(serverFile, contentClientFile.c_str(), contentClientFile.size());
			sftp_close(serverFile);

			if (nWritten != contentClientFile.size())
			{
				return false;
			}

			return true;
		}

		bool SFTPConnection::rename(const std::string& srcFile, const std::string& dstFile)
		{
			return sftp_rename(m_sftpSession, srcFile.c_str(), dstFile.c_str()) == SSH_OK;
		}

		void SFTPConnection::close()
		{
			if (m_sftpSession != nullptr)
			{
				sftp_free(m_sftpSession);
				m_sftpSession = nullptr;
			}

			if (m_sshSession != nullptr)
			{
				ssh_disconnect(m_sshSession);
				ssh_free(m_sshSession);
				m_sshSession = nullptr;
			}
		}

}}