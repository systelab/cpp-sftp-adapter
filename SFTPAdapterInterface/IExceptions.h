#pragma once

#include "ISFTPClientAdapter.h"

namespace systelab { namespace sftp { 

	struct SSHSessionCannotCreateException : ISFTPClientAdapter::Exception
	{
		SSHSessionCannotCreateException(const std::string& message) : Exception("SSH session can not create: " + message) {}
	};

	struct ConectionFailedException : ISFTPClientAdapter::Exception
	{
		ConectionFailedException(const std::string& message) : Exception("Connection failed: " + message) {}
	};

	struct InvalidPublicKeyException : ISFTPClientAdapter::Exception
	{
		InvalidPublicKeyException(const std::string& message) : Exception("The provided public key is invalid: " + message) {}
	};

	struct AuthenticationFailedException : ISFTPClientAdapter::Exception
	{
		AuthenticationFailedException(const std::string& message) : Exception("Authentication failed: " + message) {}
	};

	struct InvalidPrivateKeyException : ISFTPClientAdapter::Exception
	{
		InvalidPrivateKeyException(const std::string& message) : Exception("Invalid Private Key: " + message) {}
	};

	struct AuthenticationFailedPrivateException : ISFTPClientAdapter::Exception
	{
		AuthenticationFailedPrivateException(const std::string& message) : Exception("Authentication failed using the private key: " + message) {}
	};

	struct InvalidServerPublicKeyException : ISFTPClientAdapter::Exception
	{
		InvalidServerPublicKeyException(const std::string& message) : Exception("Invalid server publik key: " + message) {}
	};

	struct ServerFingerPrintNotAcceptedException : ISFTPClientAdapter::Exception
	{
		ServerFingerPrintNotAcceptedException(const std::string& message) : Exception("The obtained server finger print is not accepted: " + message) {}
	};

	struct SFTPSessionCannotCreateException : ISFTPClientAdapter::Exception
	{
		SFTPSessionCannotCreateException(const std::string& message) : Exception("SFTP session can not create: " + message) {}
	};

	struct SFTPSessionCannotInitException : ISFTPClientAdapter::Exception
	{
		SFTPSessionCannotInitException(const std::string& message) : Exception("SFTP session can not initialize: " + message) {}
	};

	struct InvalidConnectionException : ISFTPClientAdapter::Exception
	{
		InvalidConnectionException() : Exception("Invalid connection or not opened") {}
	};

	struct SFTPCannotCreateRemoteFileException : ISFTPClientAdapter::Exception
	{
		SFTPCannotCreateRemoteFileException(const std::string& message) : Exception("Remote file can not create: " + message) {}
	};

	struct SFTPCannotReadLocalFileException : ISFTPClientAdapter::Exception
	{
		SFTPCannotReadLocalFileException(const std::string& message) : Exception("Local file does not exist or can not be read: " + message) {}
	};

	struct SFTPCannotWriteRemoteFileException : ISFTPClientAdapter::Exception
	{
		SFTPCannotWriteRemoteFileException(const std::string& message) : Exception("Remote file can not write: " + message) {}
	};

	struct SFTPCannotRenameRemoteFileException : ISFTPClientAdapter::Exception
	{
		SFTPCannotRenameRemoteFileException(const std::string& message) : Exception("Remote file can not be rename: " + message) {}
	};
}}
