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
		// Test fixture for AnalyzeMap tests
		class AnalyzeMapTest : public ::testing::Test
		{
		protected:
			// We need to access the private static method
			std::tuple<Continuations, Continuations> CallAnalyzeMap( const BoardMap& map )
			{
				// Using the Result class to call the static method
				return Result::AnalyzeMap( map );
			}
		};

		// Test empty map handling
		TEST_F( AnalyzeMapTest, EmptyMapThrowsException )
		{
			BoardMap emptyMap;
			EXPECT_THROW( CallAnalyzeMap( emptyMap ), std::logic_error );
		}

		// Test map with empty first row
		TEST_F( AnalyzeMapTest, EmptyFirstRowThrowsException )
		{
			BoardMap mapWithEmptyFirstRow = { "" };
			EXPECT_THROW( CallAnalyzeMap( mapWithEmptyFirstRow ), std::logic_error );
		}

		// Test inconsistent map (rows with different lengths)
		TEST_F( AnalyzeMapTest, InconsistentMapThrowsException )
		{
			BoardMap inconsistentMap = {
				".....",
				"....",  // This row is shorter
				"....."
			};
			EXPECT_THROW( CallAnalyzeMap( inconsistentMap ), std::logic_error );
		}

		// Test basic map with no spaces
		TEST_F( AnalyzeMapTest, BasicMapNoSpaces )
		{
			BoardMap basicMap = {
				"...",
				"...",
				"..."
			};

			auto [columnsContinuations, rowsContinuations] = CallAnalyzeMap( basicMap );

			// Verify columns continuations
			ASSERT_EQ( columnsContinuations.size( ), 3 );
			for( int i = 0; i < 3; ++i ) {
				EXPECT_EQ( columnsContinuations[ i ].first, 0 );  // min row
				EXPECT_EQ( columnsContinuations[ i ].second, 2 ); // max row
			}

			// Verify rows continuations
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

			// First column has no non-space characters
			EXPECT_EQ( columnsContinuations[ 0 ].first, 3 );  // min row should be max int (but gets updated to 2 because of spaces)
			EXPECT_EQ( columnsContinuations[ 0 ].second, 2 ); // max row

			// Second column has a non-space character only in row 2
			EXPECT_EQ( columnsContinuations[ 1 ].first, 2 );  // min row
			EXPECT_EQ( columnsContinuations[ 1 ].second, 2 ); // max row

			// Third column has non-space characters in rows 0, 1, 2
			EXPECT_EQ( columnsContinuations[ 2 ].first, 0 );  // min row
			EXPECT_EQ( columnsContinuations[ 2 ].second, 2 ); // max row

			// Fourth and fifth columns are similar to third
			EXPECT_EQ( columnsContinuations[ 3 ].first, 0 );
			EXPECT_EQ( columnsContinuations[ 3 ].second, 2 );
			EXPECT_EQ( columnsContinuations[ 4 ].first, 0 );
			EXPECT_EQ( columnsContinuations[ 4 ].second, 2 );

			// Verify rows continuations
			ASSERT_EQ( rowsContinuations.size( ), 3 );

			// First row has non-space characters from column 2 to 4
			EXPECT_EQ( rowsContinuations[ 0 ].first, 2 );  // min column
			EXPECT_EQ( rowsContinuations[ 0 ].second, 4 ); // max column

			// Second row has non-space characters from column 1 to 4
			EXPECT_EQ( rowsContinuations[ 1 ].first, 1 );  // min column
			EXPECT_EQ( rowsContinuations[ 1 ].second, 4 ); // max column

			// Third row has non-space characters from column 0 to 4
			EXPECT_EQ( rowsContinuations[ 2 ].first, 0 );  // min column
			EXPECT_EQ( rowsContinuations[ 2 ].second, 4 ); // max column
		}

		// Test asymmetric map
		TEST_F( AnalyzeMapTest, AsymmetricMap )
		{
			BoardMap asymmetricMap = {
				"#....",
				".....",
				"....#"
			};

			auto [columnsContinuations, rowsContinuations] = CallAnalyzeMap( asymmetricMap );

			// Verify specific points for columns
			EXPECT_EQ( columnsContinuations[ 0 ].first, 0 );  // First column starts at row 0
			EXPECT_EQ( columnsContinuations[ 0 ].second, 0 ); // First column ends at row 0

			EXPECT_EQ( columnsContinuations[ 4 ].first, 2 );  // Last column starts at row 2
			EXPECT_EQ( columnsContinuations[ 4 ].second, 2 ); // Last column ends at row 2

			// Verify specific points for rows
			EXPECT_EQ( rowsContinuations[ 0 ].first, 0 );  // First row starts at column 0
			EXPECT_EQ( rowsContinuations[ 0 ].second, 0 ); // First row ends at column 0

			EXPECT_EQ( rowsContinuations[ 2 ].first, 4 );  // Last row starts at column 4
			EXPECT_EQ( rowsContinuations[ 2 ].second, 4 ); // Last row ends at column 4
		}

		// Test map with different characters
		TEST_F( AnalyzeMapTest, MapWithDifferentCharacters )
		{
			BoardMap characterMap = {
				"#.@$%",
				"&*()!",
				"12345"
			};

			auto [columnsContinuations, rowsContinuations] = CallAnalyzeMap( characterMap );

			// All non-space characters are treated equally, so all should have full ranges
			for( int i = 0; i < 5; ++i ) {
				EXPECT_EQ( columnsContinuations[ i ].first, 0 );
				EXPECT_EQ( columnsContinuations[ i ].second, 2 );
			}

			for( int i = 0; i < 3; ++i ) {
				EXPECT_EQ( rowsContinuations[ i ].first, 0 );
				EXPECT_EQ( rowsContinuations[ i ].second, 4 );
			}
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

			// Test a few key columns
			EXPECT_EQ( columnsContinuations[ 4 ].first, 0 );  // Column 4 starts at row 0
			EXPECT_EQ( columnsContinuations[ 4 ].second, 5 ); // Column 4 ends at row 5

			EXPECT_EQ( columnsContinuations[ 6 ].first, 1 );  // Column 6 starts at row 1
			EXPECT_EQ( columnsContinuations[ 6 ].second, 4 ); // Column 6 ends at row 4

			// Test a few key rows
			EXPECT_EQ( rowsContinuations[ 0 ].first, 4 );   // Row 0 starts at column 4
			EXPECT_EQ( rowsContinuations[ 0 ].second, 4 );  // Row 0 ends at column 4

			EXPECT_EQ( rowsContinuations[ 2 ].first, 1 );   // Row 2 starts at column 1
			EXPECT_EQ( rowsContinuations[ 2 ].second, 7 );  // Row 2 ends at column 7
		}

		// Test extremely large map dimensions
		TEST_F( AnalyzeMapTest, LargeMapDimensions )
		{
			// Create a large map (100x100)
			const size_t size = 100;
			BoardMap largeMap( size, std::string( size, '.' ) );

			// Add some spaces in specific positions
			largeMap[ 10 ] = std::string( 10, ' ' ) + std::string( size - 10, '.' );
			largeMap[ 20 ] = std::string( 20, ' ' ) + std::string( size - 20, '.' );

			auto [columnsContinuations, rowsContinuations] = CallAnalyzeMap( largeMap );

			// Check dimensions
			EXPECT_EQ( columnsContinuations.size( ), size );
			EXPECT_EQ( rowsContinuations.size( ), size );

			// Check specific columns with spaces
			for( int i = 0; i < 10; ++i ) {
				EXPECT_EQ( columnsContinuations[ i ].first, 0 );
				EXPECT_EQ( columnsContinuations[ i ].second, 99 );
			}

			// Check specific rows with spaces
			EXPECT_EQ( rowsContinuations[ 10 ].first, 10 );
			EXPECT_EQ( rowsContinuations[ 10 ].second, 99 );

			EXPECT_EQ( rowsContinuations[ 20 ].first, 20 );
			EXPECT_EQ( rowsContinuations[ 20 ].second, 99 );
		}

		// Additional test to verify the exact sample given in your Advent of Code problem
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

			// Verify some specific expected values based on the sample
			// First 8 columns in first 4 rows are spaces
			for( int i = 0; i < 8; ++i ) {
				EXPECT_EQ( columnsContinuations[ i ].first, 4 );  // These columns start at row 4
			}

			// Last column in first section is at index 11
			EXPECT_EQ( rowsContinuations[ 0 ].first, 8 );   // Row 0 starts at column 8
			EXPECT_EQ( rowsContinuations[ 0 ].second, 11 ); // Row 0 ends at column 11

			// Row 8 has a longer range
			EXPECT_EQ( rowsContinuations[ 8 ].first, 8 );   // Row 8 starts at column 8
			EXPECT_EQ( rowsContinuations[ 8 ].second, 15 ); // Row 8 ends at column 15
		}
	}
}