#pragma once

#include <string>

namespace systelab { namespace sftp {
	class IConnection
	{
	public:
		virtual bool isConnected() const = 0;

		virtual void upload(const std::string& srcFile, const std::string& dstFile) = 0;
//		virtual void download(const std::string& srcFile, const std::string& dstFile) = 0;  TBD
		
		virtual void rename(const std::string& srcFile, const std::string& dstFile) = 0;

		virtual void close() = 0;
	};
}}
