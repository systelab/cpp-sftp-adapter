#pragma once

#include "IConnection.h"


namespace systelab { namespace sftp {namespace test_utility {

	class MockConnection: public IConnection
	{
	public:
		MockConnection() = default;
		virtual ~MockConnection() = default;

		MOCK_CONST_METHOD0(isConnected, bool());
		MOCK_METHOD2(upload, bool(const std::string&, const std::string&));
		MOCK_METHOD2(rename, bool(const std::string&, const std::string&));
		MOCK_METHOD0(close, void());
	};
}}}

