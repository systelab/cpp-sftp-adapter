#pragma once

#include <string>

namespace systelab { namespace sftp {
	class IConnection
	{
	public:
		virtual bool isConnected() const = 0;

		virtual bool upload(const std::string& srcFile, const std::string& dstFile) = 0;
//		virtual bool download(const std::string& srcFile, const std::string& dstFile) = 0;  TBD
		
		virtual bool rename(const std::string& srcFile, const std::string& dstFile) = 0;

		virtual void close() = 0;
	};
}}
