export module monkey_math:tests;

import :types;
import :result;

import <gtest/gtest.h>;

namespace monkey_math
{
	namespace tests
	{
		TEST( ProcessLine, GivenValidLine_ExpectValidResult )
		{
			std::string validLine = "smth: after";
			auto splitResult = Result::ProcessLine( validLine );

			ASSERT_TRUE( splitResult.has_value( ) );
			EXPECT_EQ( splitResult->first, "smth" );
			EXPECT_EQ( splitResult->second, "after" );
		}

		TEST( ProcessLine, GiveTooShortLine_ExpectEmptyResult )
		{
			std::string validLine = "smth: ";
			auto splitResult = Result::ProcessLine( validLine );

			ASSERT_FALSE( splitResult.has_value( ) );
		}

		TEST( ProcessLine, GiveInvalidFormat_ExpectExceptionThrown )
		{
			std::string validLine = "invalid line";
			EXPECT_THROW( Result::ProcessLine( validLine ), std::runtime_error );
		}

	}
}