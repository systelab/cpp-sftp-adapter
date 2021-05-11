# SFTPAdapter - API to operate with an SFTP server implemented using libssh

This project is a wrapper over the libssh library to offer a simplified interface to operate with an SFTP server.

## SFTPAdapterInterface
The library interface is composed of 2 classes, the ISFTPClient class and the ISFTPConnection class.
### ISFTPClientAdapter interface
    std::unique_ptr<IConnection> connect (  const std::string& ip,
											unsigned int port,
											const std::string& username,
											const std::string& pubKeyFile,
											const std::string& privKeyFile,
											const std::function<std::string()>& getPrivKeyPassPhraseFn,
											const std::vector<std::string>& serverFingerPrints)
The connect function tries to open a connection to the SFTP server, validate the server public key against a list of provided public key fingerprints, and authenticate using a given username and private key. Then returns a IConnection object which can be used to perform operations with that connection.
#### Parameters
* **ip**: IP address of the server
* **port**: Port of the server
* **username**: Username to use to authenticate with the server
* **pubKeyFile**: Path to the file that contains the public key to use during authentication
* **privKeyFile**: Path to the file that contains the private key to use during authentication
* **getPrivKeyPassPhraseFn**: Function that returns the passphrase used to access the private key from the privKeyFile
* **serverFingerPrints**: List of valid server fingerprints. Fingerprints shall be given as SHA256 strings, with each byte separated by a colon and represented as 2 hex characters (_e.g.: `11:22:33:44:55:66:77:88:99:00:aa:bb:cc:dd:ee:ff:8c:c7:4a:f5:42:a6:4b:64:07:6b:03:ec:c8:0a:ab:9e_`)

### IConnection interface
    bool isConnected() const
Returns if the IConnection object is correctly connected or not

	bool upload(const std::string& srcFile, const std::string& dstFile)
Creates a file called dstFile in the server to which the IConnection object is connected, and fills it with the contents of the srcFile.
#### Parameters
* **srcFile**: Path to the source file in the local filesystem
* **dstFile**: Path to the target file in the SFTP server

	bool rename(const std::string& srcFile, const std::string& dstFile)
Renames the server file srcFile to dstFile
#### Parameters
* **srcFile**: Path to the file to be renamed in the SFTP server
* **dstFile**: New name of the file 

    virtual void close()
Closes the connection. After calling this function any call to isConnected() will return false.

### SftpLibsshAdapter
The implementation using libssh, implements these two interfaces through the SFTPClient and SFTPConnection classes.

### Usage
To establish a connection with an SFTP server, instantiate the SFTPClient class and call the connect method to obtain a pointer to an instance of the connection.
Then use the connection class methods to operate with the server.
