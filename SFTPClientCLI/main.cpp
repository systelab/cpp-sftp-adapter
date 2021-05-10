#include <iostream>
#include <string> 
#include <vector> 
#include <fstream>
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
	std::cout << "pubKeyFile (only base64 format is accepted for the public key)" << std::endl;
	std::cout << "privKeyFile (in openSSH format)" << std::endl;
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


std::string privKeyPassPhrase = "-";
const std::string& getPrivKeyPassPhrase()
{
	return privKeyPassPhrase;
}


int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printUsage();
		return -1;
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
		return -1;
	}

	if (fileContent.size() < 7)
	{
		std::cout << "Not enough arguments declared in the connectionDataFile content" << std::endl;
		printUsage();
		return -1;
	}


	const std::string& ip = fileContent[0];
	int port = atoi(fileContent[1].c_str());
	if (port == 0)
	{
		std::cout << "Invalid port number declared in the connectionDataFile content" << std::endl;
		return -1;
	}
	const std::string& username = fileContent[2];
	const std::string& pubKeyFile = fileContent[3];
	const std::string& privKeyFile = fileContent[4];

	privKeyPassPhrase = fileContent[5]; // It's assumed in a real implementation, some kind of obfuscation or encryptation process must be apply

	std::vector<std::string> validservers;
	for (size_t i = 6; i < fileContent.size(); i++)
	{
		validservers.push_back(fileContent[i]);
	}

	
	systelab::sftp::SFTPClient sftp;
	auto conn = sftp.Connect(ip, port, username, pubKeyFile, privKeyFile, getPrivKeyPassPhrase, validservers);

	if (!conn->isConnected())
	{
		return -2;
	}
	else
	{
		int res = 0;
		if (!conn->upload(argv[2], argv[3]))
		{
			res = -3;
		}
		else
		{
			if (argc > 3)
			{
				if (!conn->rename(argv[3], argv[4]))
				{
					res = -4;
				}
			}
		}

		conn->close();
		return res;
	}

}

