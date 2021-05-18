# SFTPAdapter - API to operate with an SFTP server implemented using libssh

This project is a wrapper over the libssh library to offer a simplified interface to operate with an SFTP server.

## SFTPAdapterInterface
The library interface is composed of 2 classes, the ISFTPClient class and the ISFTPConnection class.
### ISFTPClientAdapter interface
    std::unique_ptr<IConnection> connect (  const std::string& ip,
											unsigned int port,
											const std::string& username,
											const std::string& pubKey,
											const std::string& privKey,
											const std::function<std::string()>& getPrivKeyPassPhraseFn,
											const std::vector<std::string>& serverFingerPrints)
The connect function tries to open a connection to the SFTP server, validate the server public key against a list of provided public key fingerprints, and authenticate using a given username and private key. Then returns a IConnection object which can be used to perform operations with that connection.
#### Parameters
* **ip**: IP address of the server
* **port**: Port of the server
* **username**: Username to use to authenticate with the server
* **pubKey**: The public key in Base64 format to use during authentication
* **privKey**: The private key in OpenSSH format to use during authentication
* **getPrivKeyPassPhraseFn**: Function that returns the passphrase used to access the private key
* **serverFingerPrints**: List of valid server fingerprints. Fingerprints shall be given as SHA256 strings, with each byte separated by a colon and represented as 2 hex characters (_e.g.: `11:22:33:44:55:66:77:88:99:00:aa:bb:cc:dd:ee:ff:8c:c7:4a:f5:42:a6:4b:64:07:6b:03:ec:c8:0a:ab:9e`_)
#### Exceptions
* **SSHSessionCannotCreateException**: There was an internal error trying to instantiate the SSH session
* **ConectionFailedException**: A connection to the server could not be established (review IP/port)
* **InvalidPublicKeyException**: The provided public key is not valid
* **AuthenticationFailedException**: The server rejected the authentication with the provided username and public key
* **InvalidPrivateKeyException**: The provided private key cannot be imported
* **AuthenticationFailedPrivateException**: The provided private key could not be used to authenticate with the server
* **InvalidServerPublicKeyException**: The server did not provide a valid public key
* **ServerFingerPrintNotAcceptedException**: The fingerprint of the public key of the server was not found in the list serverFingerPrints
	* *std::string fingerprint*: Fingerprint of the server
* **SFTPSessionCannotCreateException**: There was an internal error trying to instantiate the SFTP session
* **SFTPSessionCannotInitException**: The SFTP session could not be initialized (review that the server is a SFTP server)

---

### IConnection interface
    bool isConnected() const
Returns if the IConnection object is correctly connected or not

---

	bool upload(const std::string& srcFile, const std::string& dstFile)
Creates a file called dstFile in the server to which the IConnection object is connected, and fills it with the contents of the srcFile.
#### Parameters
* **srcFile**: Path to the source file in the local filesystem
* **dstFile**: Path to the target file in the SFTP server
#### Exceptions
* **InvalidConnectionException**: The IConnection object is not connected (the isConnected() method returns false)
* **SFTPCannotCreateRemoteFileException**: The remote file could not be created in the server 
* **SFTPCannotReadLocalFileException**: The local file could not be read
* **SFTPCannotWriteRemoteFileException**: The remote file could not be written to
---

	bool rename(const std::string& srcFile, const std::string& dstFile)
Renames the server file srcFile to dstFile
#### Parameters
* **srcFile**: Path to the file to be renamed in the SFTP server
* **dstFile**: New name of the file 
#### Exceptions
* **InvalidConnectionException**: The Connection object is not connected (the isConnected() method returns false)
* **SFTPCannotRenameRemoteFileException**: The file could not be renamed in the server
---

    void close()
Closes the connection. After calling this function any call to isConnected() will return false.

---

## SftpLibsshAdapter
The implementation using libssh (https://www.libssh.org/), implements these two interfaces through the SFTPClient and SFTPConnection classes.

## Usage
To establish a connection with an SFTP server, instantiate the SFTPClient class and call the connect method to obtain a pointer to an instance of the connection.
Then use the connection class methods to operate with the server.
