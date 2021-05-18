#include <iostream>
#include <string> 
#include <vector> 
#include <fstream>
#include <functional>
#include <stdlib.h>  

#include "SftpLibsshAdapter/SFTPClient.h"
#include "SftpLibsshAdapter/SFTPConnection.h"

void printUsage()
{
	std::cout << "Usage SFTPClientCLI connectionDataFile sourceFile destinationFile {renameFilename}" << std::endl;
	std::cout << "E.g. SFTPClientCLI c:\\sftptest\\conndata.txt c:\\sftptest\\test1.txt uploaded1.txt" << std::endl;
	std::cout << "E.g. SFTPClientCLI c:\\sftptest\\conndata.txt c:\\sftptest\\test2.txt uploaded2.txt uploaded.zip" << std::endl;
	std::cout << std::endl;
	std::cout << "[ConnectionDataFile] = text file with:" << std::endl;
	std::cout << "ip" << std::endl;
	std::cout << "port" << std::endl;
	std::cout << "username" << std::endl;
	std::cout << "pubKeyFile (base64 format)" << std::endl;
	std::cout << "privKeyFile (openSSH format)" << std::endl;
	std::cout << "passphrase for the privKeyFile" << std::endl;
	std::cout << "serverFingerPrint1 (e.g.: 11:22:33:44:55:66:77:88:99:00:aa:bb:cc:dd:ee:ff:8c:c7:4a:f5:42:a6:4b:64:07:6b:03:ec:c8:0a:ab:9e)" << std::endl;
	std::cout << "{serverFingerPrint2} (optional)" << std::endl;
	std::cout << "{serverFingerPrint3} (optional)" << std::endl;
	std::cout << "{...}" << std::endl;
	std::cout << std::endl;
	std::cout << "returns:" << std::endl;
	std::cout << "	 0 if anything goes fine" << std::endl;
	std::cout << "	-1 if there is any trouble with the arguments" << std::endl;
	std::cout << "	-2 if the connection with SFTP server fails" << std::endl;
	std::cout << "	-3 if the file can't be uploaded to the server" << std::endl;
	std::cout << "	-4 if the file can't be renamed" << std::endl;
}

std::string readFileContent(const std::string filename)
{
	std::string content = "";
	try
	{
		std::ifstream file(filename);
		if (file)
		{
			file.seekg(0, std::ios::end);
			content.reserve((unsigned int)file.tellg());
			file.seekg(0, std::ios::beg);

			content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		}
	}
	catch (...) {}
	return content;
}

enum ResultErrorCodes
{
	PROCESSED_OK = 0,
	INVALID_PARAMETERS = -1,
	CONNECTION_FAILED = -2,
	UPLOAD_FAILED = -3,
	RENAME_FAILED = -4
};

std::string privKeyPassPhrase = "-";
std::string getPrivKeyPassPhrase()
{
	return privKeyPassPhrase;
}


int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printUsage();
		return ResultErrorCodes::INVALID_PARAMETERS;
	}


	std::string line;
	std::vector<std::string> fileContent;
	std::ifstream connFile(argv[1]);
	if (connFile.is_open())
	{
		while (getline(connFile, line))
		{
			fileContent.push_back(line);
		}
		connFile.close();
	}
	else
	{
		std::cout << "Unable to open connectionDataFile: " << argv[1] << std::endl;
		return ResultErrorCodes::INVALID_PARAMETERS;
	}

	if (fileContent.size() < 7)
	{
		std::cout << "Not enough arguments declared in the connectionDataFile content" << std::endl;
		printUsage();
		return ResultErrorCodes::INVALID_PARAMETERS;
	}


	const std::string& ip = fileContent[0];
	int port = atoi(fileContent[1].c_str());
	if (port == 0)
	{
		std::cout << "Invalid port number declared in the connectionDataFile content" << std::endl;
		return ResultErrorCodes::INVALID_PARAMETERS;
	}
	const std::string& username = fileContent[2];
	const std::string& pubKey = readFileContent(fileContent[3]);
	const std::string& privKey = readFileContent(fileContent[4]);

	privKeyPassPhrase = fileContent[5]; // It's assumed in a real implementation, some kind of obfuscation or encryptation process must be apply

	std::vector<std::string> validservers;
	for (size_t i = 6; i < fileContent.size(); i++)
	{
		validservers.push_back(fileContent[i]);
	}

	
	systelab::sftp::SFTPClient sftp;
	std::unique_ptr<systelab::sftp::IConnection> conn;
	try
	{
		conn = sftp.connect(ip, port, username, pubKey, privKey, getPrivKeyPassPhrase, validservers);
	}
	catch (systelab::sftp::Exception exc)
	{
		std::cout << "Error connecting (check the connectionDataFile content)" << std::endl << exc.what() << std::endl;
		return ResultErrorCodes::CONNECTION_FAILED;
	}

	if (!conn->isConnected())
	{
		std::cout << "Server not connected: check the connectionDataFile content" << std::endl;
		return ResultErrorCodes::CONNECTION_FAILED;
	}

	int res = ResultErrorCodes::PROCESSED_OK;
	try
	{
		conn->upload(argv[2], argv[3]);
	}
	catch (systelab::sftp::Exception exc)
	{
		std::cout << "Error uploading the file: " << exc.what() << std::endl;
		res = ResultErrorCodes::UPLOAD_FAILED;
	}
		
	if (res == ResultErrorCodes::PROCESSED_OK)
	{
		std::cout << "Upload complete" << std::endl;
		if (argc > 4)
		{
			try
			{
				conn->rename(argv[3], argv[4]);
				std::cout << "File renamed" << std::endl;
			}
			catch (systelab::sftp::Exception exc)
			{
				std::cout << "Error renaming the file on the server: " << exc.what() << std::endl;
				res = ResultErrorCodes::RENAME_FAILED;
			}
		}
	}

	conn->close();
	return res;
}

