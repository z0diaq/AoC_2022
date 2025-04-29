export module monkey_map:tests;

import :types;
import :result;

import <gtest/gtest.h>;

namespace monkey_map
{
	namespace tests
	{
		TEST( SomeTest, DummyTest1 )
		{
			EXPECT_TRUE( true );
		}
	}
}