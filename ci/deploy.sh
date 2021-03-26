#!/bin/bash

function checkErrors
{
	if [ $? != 0 ]
	then
		echo 
		echo "An error occured while deploying artifacts."
		echo
		exit 1
	fi
}

function parseParameters
{
	VERSION="None"
	while getopts "hv:" OPTION
	do
		case $OPTION in
		h)
			usage #help: show usage section
			exit 0
			;;
		v)
			VERSION=$OPTARG
			;;
		?)
			echo "Invalid parameter" 
			usage
			exit 1
			;;
		esac
	done
	
	echo "********** DEPLOY PARAMETERS **********"
	echo "VERSION: $VERSION"
}

parseParameters "${@}"

echo -e "\nUploading SFTPAdapterInterface/$VERSION@systelab/stable to systelab-public...\n\n"
conan upload "SFTPAdapterInterface/$VERSION@systelab/stable" --all -r systelab-public --force
checkErrors

echo -e "\nUploading SFTPAdapterInterfaceTestUtilities/$VERSION@systelab/stable to systelab-public...\n\n"
conan upload "SFTPAdapterInterfaceTestUtilities/$VERSION@systelab/stable" --all -r systelab-public --force
checkErrors
