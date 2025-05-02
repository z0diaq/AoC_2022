export module monkey_map:tests;

import :types;
import :result;

import <gtest/gtest.h>;
import <stdexcept>;
import <string>;
import <vector>;
import <tuple>;

namespace monkey_map
{
	namespace tests
	{
		class AnalyzeMapTest : public ::testing::Test
		{
		protected:
			std::tuple<Continuations, Continuations> CallAnalyzeMap( const BoardMap& map )
			{
				return Result::AnalyzeMap( map );
			}
		};

		TEST_F( AnalyzeMapTest, EmptyMapThrowsException )
		{
			BoardMap emptyMap;
			EXPECT_THROW( CallAnalyzeMap( emptyMap ), std::logic_error );
		}

		TEST_F( AnalyzeMapTest, EmptyFirstRowThrowsException )
		{
			BoardMap mapWithEmptyFirstRow = { "" };
			EXPECT_THROW( CallAnalyzeMap( mapWithEmptyFirstRow ), std::logic_error );
		}

		TEST_F( AnalyzeMapTest, BasicMapNoSpaces )
		{
			BoardMap basicMap = {
				"...",
				"...",
				"..."
			};

			auto [columnsContinuations, rowsContinuations] = CallAnalyzeMap( basicMap );

			ASSERT_EQ( columnsContinuations.size( ), 3 );
			for( int i = 0; i < 3; ++i ) {
				EXPECT_EQ( columnsContinuations[ i ].first, 0 );  // min row
				EXPECT_EQ( columnsContinuations[ i ].second, 2 ); // max row
			}

			ASSERT_EQ( rowsContinuations.size( ), 3 );
			for( int i = 0; i < 3; ++i ) {
				EXPECT_EQ( rowsContinuations[ i ].first, 0 );  // min column
				EXPECT_EQ( rowsContinuations[ i ].second, 2 ); // max column
			}
		}

		// Test map with spaces
		TEST_F( AnalyzeMapTest, MapWithSpaces )
		{
			BoardMap mapWithSpaces = {
				"  ...",
				" ....",
				"....."
			};

			auto [columnsContinuations, rowsContinuations] = CallAnalyzeMap( mapWithSpaces );

			// Verify columns continuations
			ASSERT_EQ( columnsContinuations.size( ), 5 );

			EXPECT_EQ( columnsContinuations[ 0 ].first, 2 );  // min row
			EXPECT_EQ( columnsContinuations[ 0 ].second, 2 ); // max row

			EXPECT_EQ( columnsContinuations[ 1 ].first, 1 );  // min row
			EXPECT_EQ( columnsContinuations[ 1 ].second, 2 ); // max row

			EXPECT_EQ( columnsContinuations[ 2 ].first, 0 );  // min row
			EXPECT_EQ( columnsContinuations[ 2 ].second, 2 ); // max row

			EXPECT_EQ( columnsContinuations[ 3 ].first, 0 );
			EXPECT_EQ( columnsContinuations[ 3 ].second, 2 );
			EXPECT_EQ( columnsContinuations[ 4 ].first, 0 );
			EXPECT_EQ( columnsContinuations[ 4 ].second, 2 );

			ASSERT_EQ( rowsContinuations.size( ), 3 );

			EXPECT_EQ( rowsContinuations[ 0 ].first, 2 );  // min column
			EXPECT_EQ( rowsContinuations[ 0 ].second, 4 ); // max column

			EXPECT_EQ( rowsContinuations[ 1 ].first, 1 );  // min column
			EXPECT_EQ( rowsContinuations[ 1 ].second, 4 ); // max column

			EXPECT_EQ( rowsContinuations[ 2 ].first, 0 );  // min column
			EXPECT_EQ( rowsContinuations[ 2 ].second, 4 ); // max column
		}

		// Test asymmetric map
		TEST_F( AnalyzeMapTest, AsymmetricMap )
		{
			BoardMap asymmetricMap = {
				" #...",
				".....",
				"...#"
			};

			auto [columnsContinuations, rowsContinuations] = CallAnalyzeMap( asymmetricMap );

			EXPECT_EQ( columnsContinuations[ 0 ].first, 1 );
			EXPECT_EQ( columnsContinuations[ 0 ].second, 2 );

			EXPECT_EQ( columnsContinuations[ 4 ].first, 0 );
			EXPECT_EQ( columnsContinuations[ 4 ].second, 1 );

			EXPECT_EQ( rowsContinuations[ 0 ].first, 1 );
			EXPECT_EQ( rowsContinuations[ 0 ].second, 4 );

			EXPECT_EQ( rowsContinuations[ 2 ].first, 0 );
			EXPECT_EQ( rowsContinuations[ 2 ].second, 3 );
		}

		// Test map with different characters
		TEST_F( AnalyzeMapTest, MapWithDifferentCharacters )
		{
			BoardMap characterMap = {
				"#.@$%",
				"&*()!",
				"12345"
			};

			EXPECT_THROW( CallAnalyzeMap( characterMap ), std::logic_error );
		}

		// Test map with mixed spaces and non-spaces
		TEST_F( AnalyzeMapTest, ComplexMixedMap )
		{
			BoardMap complexMap = {
				"    #         ",
				"  #####       ",
				" #######      ",
				"   #####      ",
				"    ###       ",
				"     #        "
			};

			auto [columnsContinuations, rowsContinuations] = CallAnalyzeMap( complexMap );

			EXPECT_EQ( columnsContinuations[ 4 ].first, 0 );
			EXPECT_EQ( columnsContinuations[ 4 ].second, 4 );

			EXPECT_EQ( columnsContinuations[ 6 ].first, 1 );
			EXPECT_EQ( columnsContinuations[ 6 ].second, 4 );

			EXPECT_EQ( rowsContinuations[ 0 ].first, 4 );
			EXPECT_EQ( rowsContinuations[ 0 ].second, 4 );

			EXPECT_EQ( rowsContinuations[ 2 ].first, 1 );
			EXPECT_EQ( rowsContinuations[ 2 ].second, 7 );
		}

		// Test extremely large map dimensions
		TEST_F( AnalyzeMapTest, LargeMapDimensions )
		{
			const size_t size = 100;
			BoardMap largeMap( size, std::string( size, '.' ) );

			largeMap[ 10 ] = std::string( 10, ' ' ) + std::string( size - 10, '.' );
			largeMap[ 20 ] = std::string( 20, ' ' ) + std::string( size - 20, '.' );

			auto [columnsContinuations, rowsContinuations] = CallAnalyzeMap( largeMap );

			EXPECT_EQ( columnsContinuations.size( ), size );
			EXPECT_EQ( rowsContinuations.size( ), size );

			for( int i = 0; i < 10; ++i ) {
				EXPECT_EQ( columnsContinuations[ i ].first, 0 );
				EXPECT_EQ( columnsContinuations[ i ].second, 99 );
			}

			EXPECT_EQ( rowsContinuations[ 10 ].first, 10 );
			EXPECT_EQ( rowsContinuations[ 10 ].second, 99 );

			EXPECT_EQ( rowsContinuations[ 20 ].first, 20 );
			EXPECT_EQ( rowsContinuations[ 20 ].second, 99 );
		}

		TEST_F( AnalyzeMapTest, AdventOfCodeSample )
		{
			BoardMap adventSample = {
				"        ...#",
				"        .#..",
				"        #...",
				"        ....",
				"...#.......#",
				"........#...",
				"..#....#....",
				"..........#.",
				"        ...#....",
				"        .....#..",
				"        .#......",
				"        ......#."
			};

			auto [columnsContinuations, rowsContinuations] = CallAnalyzeMap( adventSample );

			for( int i = 0; i < 8; ++i )
				EXPECT_EQ( columnsContinuations[ i ].first, 4 );  // These columns start at row 4

			EXPECT_EQ( rowsContinuations[ 0 ].first, 8 );   // Row 0 starts at column 8
			EXPECT_EQ( rowsContinuations[ 0 ].second, 11 ); // Row 0 ends at column 11

			EXPECT_EQ( rowsContinuations[ 8 ].first, 8 );   // Row 8 starts at column 8
			EXPECT_EQ( rowsContinuations[ 8 ].second, 15 ); // Row 8 ends at column 15
		}

		// Tests for GetActions method

		class GetActionsTest : public ::testing::Test
		{
		protected:
			Actions CallGetActions( const std::string& path )
			{
				return Result::GetActions( path );
			}

			bool IsNumber( const Action& action )
			{
				return std::holds_alternative<int>( action );
			}

			bool IsTurn( const Action& action )
			{
				return std::holds_alternative<Turn>( action );
			}

			int GetNumber( const Action& action )
			{
				return std::get<int>( action );
			}

			Turn GetTurn( const Action& action )
			{
				return std::get<Turn>( action );
			}
		};

		TEST_F( GetActionsTest, EmptyPathReturnsEmptyActions )
		{
			Actions actions = CallGetActions( "" );
			EXPECT_TRUE( actions.empty( ) );
		}

		TEST_F( GetActionsTest, SingleDigitNumber )
		{
			Actions actions = CallGetActions( "5" );
			ASSERT_EQ( actions.size( ), 1 );
			EXPECT_TRUE( IsNumber( actions[ 0 ] ) );
			EXPECT_EQ( GetNumber( actions[ 0 ] ), 5 );
		}

		TEST_F( GetActionsTest, MultiDigitNumber )
		{
			Actions actions = CallGetActions( "123" );
			ASSERT_EQ( actions.size( ), 1 );
			EXPECT_TRUE( IsNumber( actions[ 0 ] ) );
			EXPECT_EQ( GetNumber( actions[ 0 ] ), 123 );
		}

		TEST_F( GetActionsTest, SingleLeftTurn )
		{
			Actions actions = CallGetActions( "L" );
			ASSERT_EQ( actions.size( ), 1 );
			EXPECT_TRUE( IsTurn( actions[ 0 ] ) );
			EXPECT_EQ( GetTurn( actions[ 0 ] ), Turn::Left );
		}

		TEST_F( GetActionsTest, SingleRightTurn )
		{
			Actions actions = CallGetActions( "R" );
			ASSERT_EQ( actions.size( ), 1 );
			EXPECT_TRUE( IsTurn( actions[ 0 ] ) );
			EXPECT_EQ( GetTurn( actions[ 0 ] ), Turn::Right );
		}

		TEST_F( GetActionsTest, NumberFollowedByLeftTurn )
		{
			Actions actions = CallGetActions( "10L" );
			ASSERT_EQ( actions.size( ), 2 );
			EXPECT_TRUE( IsNumber( actions[ 0 ] ) );
			EXPECT_EQ( GetNumber( actions[ 0 ] ), 10 );
			EXPECT_TRUE( IsTurn( actions[ 1 ] ) );
			EXPECT_EQ( GetTurn( actions[ 1 ] ), Turn::Left );
		}

		TEST_F( GetActionsTest, NumberFollowedByRightTurn )
		{
			Actions actions = CallGetActions( "42R" );
			ASSERT_EQ( actions.size( ), 2 );
			EXPECT_TRUE( IsNumber( actions[ 0 ] ) );
			EXPECT_EQ( GetNumber( actions[ 0 ] ), 42 );
			EXPECT_TRUE( IsTurn( actions[ 1 ] ) );
			EXPECT_EQ( GetTurn( actions[ 1 ] ), Turn::Right );
		}

		TEST_F( GetActionsTest, TurnFollowedByNumber )
		{
			Actions actions = CallGetActions( "L7" );
			ASSERT_EQ( actions.size( ), 2 );
			EXPECT_TRUE( IsTurn( actions[ 0 ] ) );
			EXPECT_EQ( GetTurn( actions[ 0 ] ), Turn::Left );
			EXPECT_TRUE( IsNumber( actions[ 1 ] ) );
			EXPECT_EQ( GetNumber( actions[ 1 ] ), 7 );
		}

		TEST_F( GetActionsTest, ComplexPath )
		{
			Actions actions = CallGetActions( "10R5L5R10L4R5L5" );
			ASSERT_EQ( actions.size( ), 13 );

			// Check first few elements
			EXPECT_TRUE( IsNumber( actions[ 0 ] ) );
			EXPECT_EQ( GetNumber( actions[ 0 ] ), 10 );

			EXPECT_TRUE( IsTurn( actions[ 1 ] ) );
			EXPECT_EQ( GetTurn( actions[ 1 ] ), Turn::Right );

			EXPECT_TRUE( IsNumber( actions[ 2 ] ) );
			EXPECT_EQ( GetNumber( actions[ 2 ] ), 5 );

			EXPECT_TRUE( IsTurn( actions[ 3 ] ) );
			EXPECT_EQ( GetTurn( actions[ 3 ] ), Turn::Left );

			// Check last few elements
			EXPECT_TRUE( IsNumber( actions[ 10 ] ) );
			EXPECT_EQ( GetNumber( actions[ 10 ] ), 5 );

			EXPECT_TRUE( IsTurn( actions[ 11 ] ) );
			EXPECT_EQ( GetTurn( actions[ 11 ] ), Turn::Left );

			EXPECT_TRUE( IsNumber( actions[ 12 ] ) );
			EXPECT_EQ( GetNumber( actions[ 12 ] ), 5 );
		}


		TEST_F( GetActionsTest, MultipleNumbers )
		{
			// This is testing a case that shouldn't occur in valid input
			// since numbers should be separated by turns, but it's good to test
			// the parser behavior
			Actions actions = CallGetActions( "123L456" );
			ASSERT_EQ( actions.size( ), 3 );

			EXPECT_TRUE( IsNumber( actions[ 0 ] ) );
			EXPECT_EQ( GetNumber( actions[ 0 ] ), 123 );

			EXPECT_TRUE( IsTurn( actions[ 1 ] ) );
			EXPECT_EQ( GetTurn( actions[ 1 ] ), Turn::Left );

			EXPECT_TRUE( IsNumber( actions[ 2 ] ) );
			EXPECT_EQ( GetNumber( actions[ 2 ] ), 456 );
		}

		TEST_F( GetActionsTest, EndsWithNumber )
		{
			Actions actions = CallGetActions( "R10L20" );
			ASSERT_EQ( actions.size( ), 4 );

			EXPECT_TRUE( IsTurn( actions[ 0 ] ) );
			EXPECT_EQ( GetTurn( actions[ 0 ] ), Turn::Right );

			EXPECT_TRUE( IsNumber( actions[ 1 ] ) );
			EXPECT_EQ( GetNumber( actions[ 1 ] ), 10 );

			EXPECT_TRUE( IsTurn( actions[ 2 ] ) );
			EXPECT_EQ( GetTurn( actions[ 2 ] ), Turn::Left );

			EXPECT_TRUE( IsNumber( actions[ 3 ] ) );
			EXPECT_EQ( GetNumber( actions[ 3 ] ), 20 );
		}

		TEST_F( GetActionsTest, EndsWithTurn )
		{
			Actions actions = CallGetActions( "10L5R" );
			ASSERT_EQ( actions.size( ), 4 );

			EXPECT_TRUE( IsNumber( actions[ 0 ] ) );
			EXPECT_EQ( GetNumber( actions[ 0 ] ), 10 );

			EXPECT_TRUE( IsTurn( actions[ 1 ] ) );
			EXPECT_EQ( GetTurn( actions[ 1 ] ), Turn::Left );

			EXPECT_TRUE( IsNumber( actions[ 2 ] ) );
			EXPECT_EQ( GetNumber( actions[ 2 ] ), 5 );

			EXPECT_TRUE( IsTurn( actions[ 3 ] ) );
			EXPECT_EQ( GetTurn( actions[ 3 ] ), Turn::Right );
		}

		TEST_F( GetActionsTest, LargeNumbers )
		{
			Actions actions = CallGetActions( "12345L67890R12345" );
			ASSERT_EQ( actions.size( ), 5 );

			EXPECT_TRUE( IsNumber( actions[ 0 ] ) );
			EXPECT_EQ( GetNumber( actions[ 0 ] ), 12345 );

			EXPECT_TRUE( IsTurn( actions[ 1 ] ) );
			EXPECT_EQ( GetTurn( actions[ 1 ] ), Turn::Left );

			EXPECT_TRUE( IsNumber( actions[ 2 ] ) );
			EXPECT_EQ( GetNumber( actions[ 2 ] ), 67890 );

			EXPECT_TRUE( IsTurn( actions[ 3 ] ) );
			EXPECT_EQ( GetTurn( actions[ 3 ] ), Turn::Right );

			EXPECT_TRUE( IsNumber( actions[ 4 ] ) );
			EXPECT_EQ( GetNumber( actions[ 4 ] ), 12345 );
		}

		TEST_F( GetActionsTest, AdventOfCodeExample )
		{
			// Example from the problem statement
			Actions actions = CallGetActions( "10R5L5R10L4R5L5" );
			ASSERT_EQ( actions.size( ), 13 );

			// Check the sequence matches the expected pattern
			EXPECT_TRUE( IsNumber( actions[ 0 ] ) );
			EXPECT_EQ( GetNumber( actions[ 0 ] ), 10 );

			EXPECT_TRUE( IsTurn( actions[ 1 ] ) );
			EXPECT_EQ( GetTurn( actions[ 1 ] ), Turn::Right );

			EXPECT_TRUE( IsNumber( actions[ 2 ] ) );
			EXPECT_EQ( GetNumber( actions[ 2 ] ), 5 );

			EXPECT_TRUE( IsTurn( actions[ 3 ] ) );
			EXPECT_EQ( GetTurn( actions[ 3 ] ), Turn::Left );

			// Continue checking...
			EXPECT_TRUE( IsNumber( actions[ 4 ] ) );
			EXPECT_EQ( GetNumber( actions[ 4 ] ), 5 );

			EXPECT_TRUE( IsTurn( actions[ 5 ] ) );
			EXPECT_EQ( GetTurn( actions[ 5 ] ), Turn::Right );

			EXPECT_TRUE( IsNumber( actions[ 6 ] ) );
			EXPECT_EQ( GetNumber( actions[ 6 ] ), 10 );

			EXPECT_TRUE( IsTurn( actions[ 7 ] ) );
			EXPECT_EQ( GetTurn( actions[ 7 ] ), Turn::Left );

			EXPECT_TRUE( IsNumber( actions[ 8 ] ) );
			EXPECT_EQ( GetNumber( actions[ 8 ] ), 4 );

			EXPECT_TRUE( IsTurn( actions[ 9 ] ) );
			EXPECT_EQ( GetTurn( actions[ 9 ] ), Turn::Right );

			EXPECT_TRUE( IsNumber( actions[ 10 ] ) );
			EXPECT_EQ( GetNumber( actions[ 10 ] ), 5 );

			EXPECT_TRUE( IsTurn( actions[ 11 ] ) );
			EXPECT_EQ( GetTurn( actions[ 11 ] ), Turn::Left );

			EXPECT_TRUE( IsNumber( actions[ 12 ] ) );
			EXPECT_EQ( GetNumber( actions[ 12 ] ), 5 );
		}

		TEST_F( GetActionsTest, ZeroMoves )
		{
			Actions actions = CallGetActions( "0R0L0" );
			ASSERT_EQ( actions.size( ), 5 );

			EXPECT_TRUE( IsNumber( actions[ 0 ] ) );
			EXPECT_EQ( GetNumber( actions[ 0 ] ), 0 );

			EXPECT_TRUE( IsTurn( actions[ 1 ] ) );
			EXPECT_EQ( GetTurn( actions[ 1 ] ), Turn::Right );

			EXPECT_TRUE( IsNumber( actions[ 2 ] ) );
			EXPECT_EQ( GetNumber( actions[ 2 ] ), 0 );

			EXPECT_TRUE( IsTurn( actions[ 3 ] ) );
			EXPECT_EQ( GetTurn( actions[ 3 ] ), Turn::Left );

			EXPECT_TRUE( IsNumber( actions[ 4 ] ) );
			EXPECT_EQ( GetNumber( actions[ 4 ] ), 0 );
		}
	}
}