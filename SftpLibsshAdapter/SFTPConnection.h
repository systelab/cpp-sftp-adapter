#pragma once

#include "DLLImpExp.h"
#include "SFTPAdapterInterface/IConnection.h"
#include "SFTPAdapterInterface/IExceptions.h"

#include <libssh/libssh.h>
#include <libssh/sftp.h>

namespace systelab { namespace sftp {
	
	class SFTPLIBSSHADAPTER_API SFTPConnection : public IConnection
	{
	public:
		SFTPConnection() = default;
		~SFTPConnection();

		void connect(const std::string& ip,
					 unsigned int port,
					 const std::string& username,
					 const std::string& pubKeyFile,
					 const std::string& privKeyFile,
					 const std::function<std::string()>& getPrivKeyPassPhraseFn,
					 const std::vector<std::string>& serverFingerPrints);

		bool isConnected() const override;
		void upload(const std::string& srcFile, const std::string& dstFile) override;
		void rename(const std::string& srcFile, const std::string& dstFile) override;
		void close() override;

	private:
		void sshConnect(const std::string& ip, unsigned int port);
		void sshAuthorize(const std::string& username, const std::string& pubKeyFile,
						  const std::string& privKeyFile, const std::string& privKeyPassPhrase);
		void verifySFTPServerIdentity(const std::vector<std::string>& serverFingerPrints);
		void sftpConnect();

		ssh_session m_sshSession;
		sftp_session m_sftpSession;
	};

}}