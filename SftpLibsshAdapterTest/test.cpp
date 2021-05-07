#include "pch.h"


TEST(TestCaseName, TestName) 
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

/*
MockSFTPClientAdapter

	call Connect return pointer != NULL


MockConnection

!! metodo connect IP, port, username, publickey, privkey, passphrase, serverfingerprints

MOCK_CONST_METHOD0(isConnected, bool());
MOCK_METHOD2(upload, bool(const std::string&, const std::string&));
MOCK_METHOD2(rename, bool(const std::string&, const std::string&));
MOCK_METHOD0(close, void());


*/