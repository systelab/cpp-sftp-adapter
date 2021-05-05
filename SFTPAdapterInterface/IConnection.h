#pragma once

#include <string>

namespace systelab { namespace sftp {
	class IConnection
	{
	public:
		virtual IConnection() = 0;
		virtual ~IConnection() = 0;

		virtual void upload(const std::string& srcFile, const std::string& dstFile) = 0;
//		virtual void download() const = 0;  TBD
		
		virtual void close() = 0;
	};
}}
