#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "IConnection.h"

namespace systelab { namespace sftp {

	class ISFTPClientAdapter
	{
	public:
		virtual IConnection Connect(const std::string& ip,
									unsigned int port,
									const std::string& username,
									const std::string& pubKeyFile,
									const std::string& privKeyFile,
									const std::string& privKeyPassPhrase,
									const vector<std::string>& serverFingerPrints) = 0;
	
		struct Exception : std::runtime_error
		{
			explicit Exception(const std::string& message)
				: std::runtime_error(message)
			{}
		};
	};
}}
