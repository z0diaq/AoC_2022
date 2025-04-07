export module grove_positioning_system:tests;

import :types;
import :result;

import <string>;
import <limits>;

import <gtest/gtest.h>;

namespace grove_positioning_system
{
	namespace tests
	{
		TEST( Parse, ValuesTest )
		{
			EXPECT_EQ( Result::Parse( "-1", 0 ), ( Value{ -1, 0 } ) );
			EXPECT_EQ( Result::Parse( "12345", 67 ), ( Value{ 12345, 67 } ) );
			EXPECT_EQ( Result::Parse( std::to_string( std::numeric_limits<int>::min( ) ), 99 ),
			           ( Value{ std::numeric_limits<int>::min( ), 99 } ) );
			EXPECT_EQ( Result::Parse( std::to_string( std::numeric_limits<int>::max( ) ), 66 ),
			           ( Value{ std::numeric_limits<int>::max( ), 66 } ) );
		}

		// TODO: add UTs for Result::Mix( )
	}
}