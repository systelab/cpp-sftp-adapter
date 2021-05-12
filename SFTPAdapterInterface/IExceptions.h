#pragma once

namespace systelab { namespace sftp { 

	struct Exception : std::runtime_error
	{
		explicit Exception(const std::string& message)
			: std::runtime_error(message)
		{}
	};


	struct SSHSessionCannotCreateException : Exception
	{
		SSHSessionCannotCreateException(const std::string& message) : Exception("SSH session can not create: " + message) {}
	};

	struct ConectionFailedException : Exception
	{
		ConectionFailedException(const std::string& message) : Exception("Connection failed: " + message) {}
	};

	struct InvalidPublicKeyException : Exception
	{
		InvalidPublicKeyException(const std::string& message) : Exception("The provided public key is invalid: " + message) {}
	};

	struct AuthenticationFailedException : Exception
	{
		AuthenticationFailedException(const std::string& message) : Exception("Authentication failed: " + message) {}
	};

	struct InvalidPrivateKeyException : Exception
	{
		InvalidPrivateKeyException(const std::string& message) : Exception("Invalid Private Key: " + message) {}
	};

	struct AuthenticationFailedPrivateException : Exception
	{
		AuthenticationFailedPrivateException(const std::string& message) : Exception("Authentication failed using the private key: " + message) {}
	};

	struct InvalidServerPublicKeyException : Exception
	{
		InvalidServerPublicKeyException(const std::string& message) : Exception("Invalid server publik key: " + message) {}
	};

	struct ServerFingerPrintNotAcceptedException : Exception
	{
		ServerFingerPrintNotAcceptedException(const std::string& message) : Exception("The obtained server finger print is not accepted: " + message) {}
	};

	struct SFTPSessionCannotCreateException : Exception
	{
		SFTPSessionCannotCreateException(const std::string& message) : Exception("SFTP session can not create: " + message) {}
	};

	struct SFTPSessionCannotInitException : Exception
	{
		SFTPSessionCannotInitException(const std::string& message) : Exception("SFTP session can not initialize: " + message) {}
	};

	struct InvalidConnectionException : Exception
	{
		InvalidConnectionException() : Exception("Invalid connection or not opened") {}
	};

	struct SFTPCannotCreateRemoteFileException : Exception
	{
		SFTPCannotCreateRemoteFileException(const std::string& message) : Exception("Remote file can not create: " + message) {}
	};

	struct SFTPCannotReadLocalFileException : Exception
	{
		SFTPCannotReadLocalFileException(const std::string& message) : Exception("Local file does not exist or can not be read: " + message) {}
	};

	struct SFTPCannotWriteRemoteFileException : Exception
	{
		SFTPCannotWriteRemoteFileException(const std::string& message) : Exception("Remote file can not write: " + message) {}
	};

	struct SFTPCannotRenameRemoteFileException : Exception
	{
		SFTPCannotRenameRemoteFileException(const std::string& message) : Exception("Remote file can not be rename: " + message) {}
	};
}}
