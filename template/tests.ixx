export module aoc_template:tests;

import :types;
import :result;

import <gtest/gtest.h>;

namespace aoc_template
{
	namespace tests
	{
		TEST( SomeTest, DummyTest1 )
		{
			EXPECT_TRUE( true );
		}
	}
}