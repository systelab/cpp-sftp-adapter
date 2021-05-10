#pragma once

#include "ISFTPClientAdapter.h"

namespace systelab { namespace sftp {namespace test_utility {

	class MockSFTPClientAdapter : public ISFTPClientAdapter
	{
    	public:
			MockSFTPClientAdapter() = default;
			virtual ~MockSFTPClientAdapter() = default;

			MOCK_CONST_METHOD0(Connect, std::unique_ptr<IConnection>(
				const std::string&, unsigned int, const std::string&, const std::string&,
				const std::string&, const std::string& (*f)(), const std::vector<std::string>&));
	};

}}}
