#pragma once

#include <string>
#include <vector>
#include <memory>

#include "IConnection.h"

namespace systelab { namespace sftp {

	class SFTPLIBSSHADAPTER_API ISFTPClientAdapter
	{
	public:
		virtual ~ISFTPClientAdapter() = default;
		virtual std::unique_ptr<IConnection> connect(const std::string& ip,
													 unsigned short port,
													 const std::string& username,
													 const std::string& pubKey,
													 const std::string& privKey,
													 const std::function<std::string()>& getPrivKeyPassPhraseFn,
													 const std::vector<std::string>& serverFingerPrints) = 0;
	};
}}
