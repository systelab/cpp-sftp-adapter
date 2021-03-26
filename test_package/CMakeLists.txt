cmake_minimum_required(VERSION 3.2)

project(SFTPAdapterPackageTestProject)

# Configure environment
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find external dependencies
find_package(SFTPAdapterInterfaceTestUtilities)

# Configure test package project
set(SFTP_ADAPTER_PACKAGE_TEST_PROJECT SFTPAdapterPackageTest)
add_executable(${SFTP_ADAPTER_PACKAGE_TEST_PROJECT} SFTPAdapterExample.cpp)
target_link_libraries(${SFTP_ADAPTER_PACKAGE_TEST_PROJECT} SFTPAdapterInterfaceTestUtilities::SFTPAdapterInterfaceTestUtilities)

# Register tests
enable_testing()
add_test(NAME SFTPAdapterPackageTest COMMAND ${SFTP_ADAPTER_PACKAGE_TEST_PROJECT})
