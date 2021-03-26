#pragma once

#include <stdexcept>
#include <string>

namespace systelab { namespace sftp {
	class ISFTPClientAdapter
	{
	public:
		virtual ~ISFTPClientAdapter() = default;

		virtual void upload() const = 0;
		virtual void download() const = 0;
		
	public:
		struct Exception : std::runtime_error
		{
			explicit Exception(const std::string& message)
				: std::runtime_error(message)
			{}
		};
	};
}}
