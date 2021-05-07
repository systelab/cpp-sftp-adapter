#pragma once

#include "ISFTPClientAdapter.h"
#include "IConnection.h"

namespace systelab { namespace sftp {

	class SFTPClient : public ISFTPClientAdapter
	{
	public:
		SFTPClient() = default;
		~SFTPClient() = default;

		std::unique_ptr<IConnection> Connect(const std::string& ip,
											 unsigned int port,
											 const std::string& username,
											 const std::string& pubKeyFile,
											 const std::string& privKeyFile,
											 const std::string& privKeyPassPhrase,
											 const std::vector<std::string>& serverFingerPrints) override;
	};

}}