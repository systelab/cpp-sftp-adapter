#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING  1

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

#include "SFTPAdapterInterfaceTestUtilities/Mocks/MockSFTPClientAdapter.h"

int main(int argc, char *argv[])
{
    systelab::sftp::test_utility::MockSFTPClientAdapter SFTPClientAdapter;
    std::cout << "SFTP adapter test utilities work as expected" << std::endl;

    return 0;
}