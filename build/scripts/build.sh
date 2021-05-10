#!/bin/bash

function parse_parameters
{
	#Parse input parameters
	while getopts "hr:s:c:p:d:v:n:" OPTION 
	do
		case $OPTION in
		r)
			ROOT_PATH=$OPTARG
			;;
		
		s)
			VS_SOLUTION=$OPTARG
			;;
			
		c)
			CONFIGS=$OPTARG
			;;
		
		p)
			PROJECTS=$OPTARG
			;;
			
		d)
			DEVENV_PATH=$OPTARG
			;;

		v)
			CONAN_PACKAGE_VERSION=$OPTARG
			;;

		n)
			CONAN_PACKAGE_CHANNEL=$OPTARG
			;;
			
		h)
			usage #help: show usage section
			exit
			;;	
			
		?)		
			echo "Invalid parameter" 
			usage
			exit
			;;
		esac
	done
}


function init_parameters
{
	CONAN_PACKAGE_VERSION="0.0.0.0"
	CONAN_PACKAGE_CHANNEL="testing"
	ROOT_PATH=""
	VS_SOLUTION=""
	CONFIGS=""
	PROJECTS=""
	
	#default path of VS
	# - use devenv.com instead of devenv.exe to make output available
	DEVENV_PATH="$VS100COMNTOOLS\\..\\IDE\\devenv.com"
}

function init_print_variables
{
	# - all slashes must be "/"; otherwise cygwin won't execute devenv  
	DEVENV_PATH=`cygpath -m "$DEVENV_PATH"`
	   
	 #"$VS80COMNTOOLS\\..\\IDE\\devenv.com"`
	
	#replace "," by " "
	CONFIGS=`echo $CONFIGS | sed 's/,/ /g'`
	PROJECTS=`echo $PROJECTS | sed 's/,/ /g'`
	
	echo
	echo
	echo "###############################################################"
	echo "Using VS from: $DEVENV_PATH"
	echo "Root path: $ROOT_PATH"
	echo "Solution: $VS_SOLUTION"
	echo "Projects: $PROJECTS"
	echo "Configurations: $CONFIGS"
	echo "Conan packages version: $CONAN_PACKAGE_VERSION"
	echo "Conan packages channel: $CONAN_PACKAGE_CHANNEL"
	echo "###############################################################"
	echo
}


function check_errors
{
	if [ $? != 0 ]
	then
		echo 
		echo "An error occured while compiling $PROJECT ($CONFIG)."
		echo
		exit 1
	fi
}

function check_parameters_validity
{
	if [[ -z $ROOT_PATH ]]
	then 
		echo
		echo "Syntax error: root path must be specified using -r option."
		exit 1
	fi
	
	if [[ -z $VS_SOLUTION ]]
	then 
		echo
		echo "Syntax error: .sln file must be specified relative to ROOT_PATH using -s option."
		exit 1
	fi
	
	if [[ -z $PROJECTS ]]
	then 
		echo
		echo "Syntax error: no projects specified. Use -p."
		exit 1
	fi

	if [[ -z $CONFIGS ]]
	then 
		echo
		echo "Syntax error: no configurations specified. Use -c."
		exit 1
	fi
}

function set_conan_package_properties
{
	PROPERTIES_FILE="conan-package.props"
	
	# Set ConanPackageVersion
	echo "Setting ConanPackageVersion to $CONAN_PACKAGE_VERSION in $PROPERTIES_FILE file"
	echo "sed -i 's/[0-9]\+\.[0-9]\+\.[0-9]\+\(\.[0-9]\+\)\?/$CONAN_PACKAGE_VERSION/' \"$PROPERTIES_FILE\""
	eval "sed -i 's/[0-9]\+\.[0-9]\+\.[0-9]\+\(\.[0-9]\+\)\?/$CONAN_PACKAGE_VERSION/' \"$PROPERTIES_FILE\""
	check_errors
	chmod 666 "$PROPERTIES_FILE"
	check_errors
	echo "Done."
	
	# Set ConanPackageChannel
	echo "Setting ConanPackageChannel to $CONAN_PACKAGE_CHANNEL in $PROPERTIES_FILE file"
	echo "sed -i 's/testing/$CONAN_PACKAGE_CHANNEL/' \"$PROPERTIES_FILE\""
	eval "sed -i 's/testing/$CONAN_PACKAGE_CHANNEL/' \"$PROPERTIES_FILE\""
	check_errors
	chmod 666 "$PROPERTIES_FILE"
	check_errors
	echo "Done."	
}



#MAIN
init_parameters					#Init global parameters to default values
parse_parameters "${@}"			#Parse command line parameters
check_parameters_validity		#Check coherence of command line parameters
init_print_variables			#initialize & print variables used internally by this script
set_conan_package_properties	#Update VS properties file with the given conan package properties

	
for PROJECT in $PROJECTS
do
	
	for CONFIG in $CONFIGS
	do		
		echo 
		echo "###################### Compiling $PROJECT ($CONFIG) #############################"
		echo
		"$DEVENV_PATH"  "$ROOT_PATH\\$VS_SOLUTION" /build "$CONFIG" /PROJECT "$PROJECT"
		#echo devenv=$?
		check_errors
		
	done #CONFIGS
	
done #PROJECTS	

exit 0