# Test execution summary

| Scenario name                                                         | Result  |
|-----------------------------------------------------------------------|---------|
| Scenario 1: Establish connection, upload documents and rename them    | &#9745; |
| Scenario 2: Cannot establish connection due to missing public key     | &#9745; |
| Scenario 3: Cannot establish connection due to missing private key    | &#9745; |
| Scenario 4: Cannot establish connection due to incorrect public key   | &#9745; |
| Scenario 5: Cannot establish connection due to incorrect private key  | &#9745; |
| Scenario 6: Cannot establish connection due to incorrect username     | &#9745; |
| Scenario 7: Error case missing sourceFile                             | &#9745; |
| Scenario 8: Error case duplicate renameFilename in destination        | &#9745; |
| Scenario 9: Error case duplicate destinationFile name in destination  | &#9745; |
| Scenario 10: Error case insuficcient rights on destination            | &#9745; |
| Scenario 11: Cannot establish connection due to incorrect IP address (IP adress assigned)  | &#9745; |
| Scenario 12: Cannot establish connection due to incorrect IP address (IP adress not assigned) | &#9745; |
| Scenario 13: Cannot establish connection due to incorrect port        | &#9745; |

# Scenario 1: Establish connection, upload documents and rename them

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states "Upload complete" and "File renamed"   |
| 2      | In destination path                                        | A new file with the specified renameFilename has been created with the same content than the fileToBeUploadedName file |

Example 1:

```
SFTPClientCLI.exe config.txt fileToBeUploadedName.txt fileUploadedName.txt fileRenamed.zip
```

# Scenario 2: Cannot establish connection due to missing public key

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.
- Remove the public key from the path specified in the connectionDataFile

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states: (see log1)    |
| 2      | In destination path                                        | No new file has been created |

log1:
```
Error connecting (check the connectionDataFile content)
The provided public key is invalid:
```

# Scenario 3: Cannot establish connection due to missing private key

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.
- Remove the private key from the path specified in the connectionDataFile

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states: (see log2)    |
| 2      | In destination path                                        | No new file has been created |

log2:
```
Error connecting (check the connectionDataFile content)
Invalid Private Key:
```

# Scenario 4: Cannot establish connection due to incorrect public key

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.
- Edit the public key in the client.

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states: (see log3)|
| 2      | In destination path                                        | No new file has been created |

log3:
```
Error connecting (check the connectionDataFile content)
The provided public key is invalid:
```

# Scenario 5: Cannot establish connection due to incorrect private key

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.
- Edit the private key in the client.

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states: (see log4)   |
| 2      | In destination path                                        | No new file has been created |

log4:
```
Error connecting (check the connectionDataFile content)
Invalid Private Key:
```

# Scenario 6: Cannot establish connection due to incorrect username

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.
- Edit the username in the connectionDataFile.

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states: (see log5)   |
| 2      | In destination path                                        | No new file has been created |

log5:

```
Error connecting (check the connectionDataFile content)                                                                 
Authentication failed using the private key: Access denied for 'publickey'. Authentication that can continue: password,keyboard-interactive,publickey  
```

# Scenario 7: Error case missing sourceFile

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.
- Remove the sourceFile from the path specified in the connectionDataFile.

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states: (see log6)   |
| 2      | In destination path                                        | No new file has been created |

log6:

```
Error uploading the file: Local file does not exist or can not be read:  
```

# Scenario 8: Error case duplicate renameFilename in destination

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.
- Place a file with the same name as specified in renameFilename option.

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states: (see log7)   |
| 2      | In destination path                                        | The file with the destinationFile name has been created |

log7:
```
Upload complete
Error renaming the file on the server: Remote file can not be rename: SFTP server: Already exists. 
```

# Scenario 9: Duplicate destinationFile name in destination

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.
- Place a file with the same name as specified in destinationFile option.

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states “Upload complete” and “File renamed”   |
| 2      | In destination path                                        | The file that was originally in the destination folder has been overwritten and renamed |


# Scenario 10: Error case insuficcient rights on destination

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.
- Point as a destionationFile to a folder that cannot be modified by the user executing the upload command.

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states: (see log8)   |
| 2      | In destination path                                        | No new file has been created |

log8:
```
Upload complete
Error uploading the file: Remote file can not create: SFTP server: Access denied.  
```

# Scenario 11: Cannot establish connection due to incorrect IP address (IP adress assigned)

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.
- Edit the connectionDataFile to point to an IP adress that is assigned (e.g. 192.168.1.1).

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states: (see log9)   |
| 2      | In destination path                                        | No new file has been created |

log9:
```
Error connecting (check the connectionDataFile content)
The obtained server finger print is not accepted:
```

# Scenario 12: Cannot establish connection due to incorrect IP address (IP adress not assigned)

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.
- Edit the connectionDataFile to point to an IP adress that is not assigned (xxx.xxx.xxx.xxx).

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states: (see log10)   |
| 2      | In destination path                                        | No new file has been created |

log10:
```
Error connecting (check the connectionDataFile content)
Connection failed: Timeout connecting to xxx.xxx.xxx.xxx <-(here the target IP)
```

# Scenario 12: Cannot establish connection due to incorrect port

**Preconditions**: 
- Prepare an SFTP Server.
- Make sure the client public key is added to the list of trusted keys in the server.
- Generate a connectionDataFile with all **valid** parameters.
- Edit the connectionDataFile to point to a different port.

| Step # | Action                                                     | Expected                                                      |
|--------|------------------------------------------------------------|---------------------------------------------------------------|
| 1      | Call the .exe file with all the parameters (see example 1) | Console message states: (see log11)   |
| 2      | In destination path                                        | No new file has been created |

log11:
```
Error connecting (check the connectionDataFile content)
Connection failed: Timeout connecting to 127.0.0.1
```

