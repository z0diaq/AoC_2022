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

		TEST( Evaluate, SingleLiteral )
		{
			MonkeyMath monkeys = {
				{ "a", "42" }
			};
			EXPECT_EQ( Result::Evaluate( monkeys, "a" ), 42 );
		}

		TEST( Evaluate, BasicAddition )
		{
			MonkeyMath monkeys = {
				{ "a", "1" },
				{ "b", "2" },
				{ "sum", "a + b" }
			};
			EXPECT_EQ( Result::Evaluate( monkeys, "sum" ), 3 );
		}

		TEST( Evaluate, BasicSubtraction )
		{
			MonkeyMath monkeys = {
				{ "a", "10" },
				{ "b", "4" },
				{ "sub", "a - b" }
			};
			EXPECT_EQ( Result::Evaluate( monkeys, "sub" ), 6 );
		}

		TEST( Evaluate, BasicMultiplication )
		{
			MonkeyMath monkeys = {
				{ "a", "7" },
				{ "b", "6" },
				{ "mul", "a * b" }
			};
			EXPECT_EQ( Result::Evaluate( monkeys, "mul" ), 42 );
		}

		TEST( Evaluate, BasicDivision )
		{
			MonkeyMath monkeys = {
				{ "a", "84" },
				{ "b", "2" },
				{ "div", "a / b" }
			};
			EXPECT_EQ( Result::Evaluate( monkeys, "div" ), 42 );
		}

		TEST( Evaluate, NestedExpressions )
		{
			MonkeyMath monkeys = {
				{ "x", "2" },
				{ "y", "3" },
				{ "sum", "x + y" },
				{ "mul", "sum * y" }
			};
			EXPECT_EQ( Result::Evaluate( monkeys, "mul" ), 15 );
		}

		TEST( Evaluate, NegativeNumbers )
		{
			MonkeyMath monkeys = {
				{ "a", "-5" },
				{ "b", "3" },
				{ "sum", "a + b" }
			};
			EXPECT_EQ( Result::Evaluate( monkeys, "sum" ), -2 );
		}

		TEST( Evaluate, UnknownMonkeyThrows )
		{
			MonkeyMath monkeys = {
				{ "a", "1" }
			};
			EXPECT_THROW( Result::Evaluate( monkeys, "b" ), std::logic_error );
		}

		TEST( Evaluate, EmptyOperationThrows )
		{
			MonkeyMath monkeys = {
				{ "a", "" }
			};
			EXPECT_THROW( Result::Evaluate( monkeys, "a" ), std::logic_error );
		}

		TEST( Evaluate, InvalidOperationPartsThrows )
		{
			MonkeyMath monkeys = {
				{ "bad", "a + " }
			};
			EXPECT_THROW( Result::Evaluate( monkeys, "bad" ), std::logic_error );
		}

		TEST( Evaluate, InvalidOperatorLengthThrows )
		{
			MonkeyMath monkeys = {
				{ "a", "1" },
				{ "b", "2" },
				{ "weird", "a ++ b" }
			};
			EXPECT_THROW( Result::Evaluate( monkeys, "weird" ), std::logic_error );
		}

		TEST( Evaluate, UnknownOperatorThrows )
		{
			MonkeyMath monkeys = {
				{ "a", "5" },
				{ "b", "2" },
				{ "badop", "a % b" }
			};
			EXPECT_THROW( Result::Evaluate( monkeys, "badop" ), std::logic_error );
		}
	}
}