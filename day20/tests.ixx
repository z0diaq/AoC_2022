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

		TEST( Mix, BasicMixTest )
		{
			// Example from AoC
			Values initialValues =
			{
				Value{1, 0},
				Value{2, 1},
				Value{-3, 2},
				Value{3, 3},
				Value{-2, 4},
				Value{0, 5},
				Value{4, 6}
			};

			Values expectedMixedValues =
			{
				Value{1, 0},
				Value{2, 1},
				Value{-3, 2},
				Value{4, 6},
				Value{0, 5},
				Value{3, 3},
				Value{-2, 4}
			};

			Values mixedValues = Result::Mix( initialValues );

			// Compare the values in the lists
			ASSERT_EQ( mixedValues.size( ), expectedMixedValues.size( ) );

			for( size_t i = 0; i < mixedValues.size( ); ++i )
				EXPECT_EQ( mixedValues[ i ].m_value, expectedMixedValues[ i ].m_value );
		}

		TEST( Mix, EdgeCasesTest )
		{
			// Test with values that are multiples of (size-1)
			Values initialValues =
			{
				Value{6, 0},  // size-1
				Value{-6, 1}, // -(size-1)
				Value{12, 2}, // 2*(size-1)
				Value{0, 3},
				Value{3, 4},
				Value{-9, 5}, // -3*(size-1)
				Value{1, 6}
			};


			Values expectedMixedValues =
			{
				Value{1, 0},
				Value{6, 1},
				Value{3, 2},
				Value{-9, 6},
				Value{-6, 5},
				Value{12, 3},
				Value{0, 4}
			};

			Values mixedValues = Result::Mix( initialValues );

			// Compare the values in the lists
			ASSERT_EQ( mixedValues.size( ), expectedMixedValues.size( ) );

			for( size_t i = 0; i < mixedValues.size( ); ++i )
				EXPECT_EQ( mixedValues[ i ].m_value, expectedMixedValues[ i ].m_value ) << " index: " << i;
		}

		TEST( Mix, LargeValuesTest )
		{
			Values initialValues =
			{
				Value{1000, 0},
				Value{-1000, 1},
				Value{1, 2},
				Value{0, 3},
				Value{-1, 4},
				Value{500, 5},
				Value{-500, 6}
			};

			Values mixedValues = Result::Mix( initialValues );

			auto zeroIt = std::find_if( mixedValues.begin( ), mixedValues.end( ),
				[ ]( const Value& value ) { return value.m_value == 0; } );
			ASSERT_NE( zeroIt, mixedValues.end( ) );

			int64_t coordinates = Result::GetCoordinates( mixedValues );
			EXPECT_NE( coordinates, 0 );
		}
	}
}