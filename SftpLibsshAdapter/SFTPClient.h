#pragma once

#include "DLLImpExp.h"
#include "ISFTPClientAdapter.h"
#include "IConnection.h"

namespace systelab { namespace sftp {

	class SFTPLIBSSHADAPTER_API SFTPClient : public ISFTPClientAdapter
	{
	public:
		SFTPClient() = default;
		~SFTPClient() = default;

		std::unique_ptr<IConnection> connect(const std::string& ip,
											 unsigned int port,
											 const std::string& username,
											 const std::string& pubKeyFile,
											 const std::string& privKeyFile,
											 std::function<std::string()> getPrivKeyPassPhraseFn,
											 const std::vector<std::string>& serverFingerPrints) override;
	};

}}