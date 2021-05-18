
#usage
function usage
{
	echo "Usage: $0 -r PATH -p PROJECTS"
	echo ""
	echo 
	echo "	-p List of CppCheck projects"
	echo "	-k List of CppCheck projects"
	echo "  -r ARG   Root path of the workspace"
}

function parse_parameters
{
	#Parse input parameters
	while getopts "hr:p:k:" OPTION 
	do
		case $OPTION in
		r)
			ROOT_PATH=$OPTARG
			;;
		
		p)
			PROJECTS=$OPTARG
			;;
			
		k)
			PACKAGES=$OPTARG
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

function check_parameters_validity
{
	if [[ -z $ROOT_PATH ]]
	then 
		echo
		echo "Syntax error: root path must be specified using -r option."
		exit 1
	fi

	if [[ -z $PROJECTS ]]
	then 
		echo
		echo "Syntax error: no projects specified. Use -p."
		exit 1
	fi
}

function init_print_variables
{
	#replace "," by " "
	PROJECTS=`echo $PROJECTS | sed 's/,/ /g'`
	
	echo
	echo
	echo "###############################################################"
	echo "Root path: $ROOT_PATH"
	echo "CppCheck Projects: $PROJECTS"
	echo "CppCheck Packages: $PACKAGES"
	echo "###############################################################"
	echo
}


parse_parameters "${@}"		#Parse command line parameters
check_parameters_validity	#Check coherence of command line parameters
init_print_variables		#initialize & print variables used internally by this script


PROJECT_INDEX=0
for PROJECT in $PROJECTS
	do	

		CPPCHECK_PACKAGE_NAME="${PACKAGES[$PROJECT_INDEX]}"
		CPP_CHECK_PROJECT="${PROJECT}\\${CPPCHECK_PACKAGE_NAME}.cppcheck"
		CPP_CHECK_XML="${CPPCHECK_PACKAGE_NAME}_cppcheck.xml"

		echo 
		echo "###################### Analyze statically project $CPPCHECK_PACKAGE_NAME #############################"
		echo
		echo "cppcheck --project='${WORKSPACE}\\${CPP_CHECK_PROJECT}' --xml '${WORKSPACE}\\${PROJECT}' 2> '${WORKSPACE}\\report\\${CPP_CHECK_XML}'"
		mkdir "${WORKSPACE}\\report"
		cppcheck --project="${WORKSPACE}\\${CPP_CHECK_PROJECT}" --xml "${WORKSPACE}\\${PROJECT}" 2> "${WORKSPACE}\\report\\${CPP_CHECK_XML}"

		PROJECT_INDEX=$((PROJECT_INDEX+1));
		
		#echo devenv=$?
		# check_errors
		
	done #PROJECTS
exit 0