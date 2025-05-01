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
	}
}