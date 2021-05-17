#include "stdafx.h"
#include "SFTPClient.h"
#include "SFTPConnection.h"

namespace systelab { namespace sftp {

		std::unique_ptr<IConnection>
			SFTPClient::connect(const std::string& ip,
								unsigned int port,
								const std::string& username,
								const std::string& pubKeyFile,
								const std::string& privKeyFile,
								const std::function<std::string()>& getPrivKeyPassPhraseFn,
								const std::vector<std::string>& serverFingerPrints)
		{
			auto conn = std::make_unique<SFTPConnection>();
			conn->connect(ip, port, username, pubKeyFile, privKeyFile, getPrivKeyPassPhraseFn, serverFingerPrints);
			return conn;
		}

}}