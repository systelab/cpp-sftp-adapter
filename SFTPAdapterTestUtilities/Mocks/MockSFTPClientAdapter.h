#pragma once

#include "SFTPAdapterInterface/ISFTPClientAdapter.h"

namespace systelab { namespace sftp { namespace test_utility {
	class MockSFTPClientAdapter : public ISFTPClientAdapter
	{
	public:
		MockSFTPClientAdapter();
		virtual ~MockSFTPClientAdapter();

		MOCK_CONST_METHOD0(upload, void());
		MOCK_CONST_METHOD0(download, void());
	};
}}}
