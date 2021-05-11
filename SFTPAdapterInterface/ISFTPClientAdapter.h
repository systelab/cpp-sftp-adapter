#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

#include "IConnection.h"

namespace systelab { namespace sftp {

	class ISFTPClientAdapter
	{
	public:
		virtual std::unique_ptr<IConnection> connect(const std::string& ip,
													 unsigned int port,
													 const std::string& username,
													 const std::string& pubKeyFile,
													 const std::string& privKeyFile,
													 std::function<std::string()> getPrivKeyPassPhraseFn,
													 const std::vector<std::string>& serverFingerPrints) = 0;
	 
		struct Exception : std::runtime_error
		{
			explicit Exception(const std::string& message)
				: std::runtime_error(message)
			{}
		};
	};
}}
