#pragma once

#include "IConnection.h"

#include <libssh/libssh.h>
#include <libssh/sftp.h>

namespace systelab { namespace sftp {

	class SFTPConnection : public IConnection
	{
	public:
		SFTPConnection();
		~SFTPConnection();

		void connect(const std::string& ip,
					 unsigned int port,
					 const std::string& username,
					 const std::string& pubKeyFile,
					 const std::string& privKeyFile,
					 const std::string& privKeyPassPhrase,
					 const std::vector<std::string>& serverFingerPrints);

		bool isConnected() const override;
		bool upload(const std::string& srcFile, const std::string& dstFile) override;
		bool rename(const std::string& srcFile, const std::string& dstFile) override;
		void close() override;

	private:
		bool sshConnect(const std::string& ip, unsigned int port);
		bool sshAuthorize(const std::string& username, const std::string& pubKeyFile,
						  const std::string& privKeyFile, const std::string& privKeyPassPhrase);
		bool verifySFTPServerIdentity(const std::vector<std::string>& serverFingerPrints);
		bool sftpConnect();

		ssh_session m_sshSession;
		sftp_session m_sftpSession;
	};

}}