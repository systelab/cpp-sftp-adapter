#pragma once

#include "DLLImpExp.h"
#include "SFTPAdapterInterface/ISFTPClientAdapter.h"
#include "SFTPAdapterInterface/IConnection.h"

namespace systelab { namespace sftp {

	class SFTPLIBSSHADAPTER_API SFTPClient : public ISFTPClientAdapter
	{
	public:
		SFTPClient() = default;
		~SFTPClient() = default;

		std::unique_ptr<IConnection> Connect(const std::string& ip,
											 unsigned int port,
											 const std::string& username,
											 const std::string& pubKeyFile,
											 const std::string& privKeyFile,
											 const std::string& (*getPrivKeyPassPhrase)(),
											 const std::vector<std::string>& serverFingerPrints) override;
	};

}}