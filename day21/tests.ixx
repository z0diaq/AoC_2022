export module monkey_math:tests;

import :types;
import :result;

import <gtest/gtest.h>;

namespace monkey_math
{
	namespace tests
	{
		TEST( SomeTest, DummyTest1 )
		{
			EXPECT_TRUE( true );
		}
	}
}