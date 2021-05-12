# Purpose
The SFTPClientCLI application can be used to test the main functions of the library.
The tool will perform a connection, upload a file, and optionally rename it.
# Usage
    SFTPClientCLI connectionDataFile sourceFile destinationFile {renameFilename}

## Examples
* _E.g. SFTPClientCLI c:\sftptest\conndata.txt c:\sftptest\test1.txt uploaded1.txt_
* _E.g. SFTPClientCLI c:\sftptest\conndata.txt c:\sftptest\test2.txt uploaded2.txt uploaded.zip_

## ConnectionDataFile
The connectionDataFile shall be a text file with the following data:

    ip
    port
    username
    pubKeyFile (only base64 format is accepted for the public key)
    privKeyFile (in openSSH format)
    serverFingerPrint1 (e.g.: 11:22:33:44:55:66:77:88:99:00:aa:bb:cc:dd:ee:ff:8c:c7:4a:f5:42:a6:4b:64:07:6b:03:ec:c8:0a:ab:9e)
    {serverFingerPrint2} (optional)
    {serverFingerPrint3} (optional)
    {...}


## Return values
* 0 if anything goes fine
* -1 if there is any trouble with the arguments
* -2 if the connection with SFTP server fails
* -3 if the file can't be uploaded to the server
* -4 if the file can't be renamed