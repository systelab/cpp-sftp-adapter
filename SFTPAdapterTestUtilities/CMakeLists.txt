cmake_minimum_required(VERSION 3.2)

# Find external dependencides
set(GTEST_PACKAGE_NAME gtest)
find_package(${GTEST_PACKAGE_NAME})
if (NOT TARGET ${GTEST_PACKAGE_NAME}::${GTEST_PACKAGE_NAME})
    set(GTEST_PACKAGE_NAME GTest)
    find_package(${GTEST_PACKAGE_NAME})
endif()

find_package(TestUtilitiesInterface)
find_package(SFTPAdapterInterface)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure SFTP Adapter test utilities project
set(SFTP_ADAPTER_TEST_UTILITIES_PROJECT SFTPAdapterInterfaceTestUtilities)
file(GLOB_RECURSE SFTP_ADAPTER_TEST_UTILITIES_PROJECT_SRC "*.cpp")
file(GLOB_RECURSE SFTP_ADAPTER_TEST_UTILITIES_PROJECT_HDR "*.h")
add_library(${SFTP_ADAPTER_TEST_UTILITIES_PROJECT} STATIC ${SFTP_ADAPTER_TEST_UTILITIES_PROJECT_SRC} ${SFTP_ADAPTER_TEST_UTILITIES_PROJECT_HDR})
target_link_libraries(${SFTP_ADAPTER_TEST_UTILITIES_PROJECT}
					  ${GTEST_PACKAGE_NAME}::${GTEST_PACKAGE_NAME}
					  TestUtilitiesInterface::TestUtilitiesInterface
					  SFTPAdapterInterface::SFTPAdapterInterface)

# Configure source groups
foreach(FILE ${SFTP_ADAPTER_TEST_UTILITIES_PROJECT_SRC} ${SFTP_ADAPTER_TEST_UTILITIES_PROJECT_HDR})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Header Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()
