import hill_climbing_algorithm;

#include <iostream>
#include <string>
#include <stdexcept>

#include <vector>
#include <deque>

using namespace hill_climbing_algorithm;

unsigned int
Result::FindShortestPathLength( )
{
	std::deque<Location> openSet;

	std::vector<std::vector<unsigned int> > scores;
	for( size_t rowNo = 0; rowNo != m_heightMap.size( ); ++rowNo )
		scores.push_back( std::vector<unsigned int>( m_heightMap[ 0 ].length( ), std::numeric_limits<unsigned int>::max( ) ) );

	auto Score = [&scores]( const Location& loc ) -> unsigned int&
	{
		return scores[ loc.m_row ][ loc.m_column ];
	};

	openSet.push_back( FindLocation( 'S' ) );
	Score( openSet.back( ) ) = 0;

	if( IsPartTwo( ) )
	{
		for( size_t rowNo = 0; rowNo != m_heightMap.size( ); ++rowNo )
		{
			const std::string& line = m_heightMap[ rowNo ];
			for( size_t columnNo = 0; columnNo != line.length( ); ++columnNo )
			{
				Location testPos{ rowNo, columnNo };
				if( Value( testPos ) == 'a' )
				{
					openSet.push_back( testPos );
					Score( testPos ) = 0;
				}
			}
		}
	}

	while( false == openSet.empty( ) )
	{
		Location testPos = openSet.front( );
		openSet.pop_front( );

		if( Value( testPos ) == 'E' )
			return Score( testPos );

		LocationsList neighbors = FindValidNeighbors( testPos );

		const unsigned int myScore = Score( testPos );
		for( const Location& neighbor : neighbors )
		{
			if( Score( neighbor ) > myScore + 1 )
			{
				openSet.push_back( neighbor );
				Score( neighbor ) = myScore + 1;
			}
		}
	}

	throw std::logic_error( "Could not find path to destination" );
}

LocationsList
Result::FindValidNeighbors( const Location& pos ) const
{
	const char myHeight = Value( pos );
	LocationsList result;
	auto CheckLocation = [myHeight, &result, this]( const Location& loc ) -> void
	{
		if( IsValid( loc ) )
		{
			const char value = Value( loc );
			if( ( value != 'E' && value != 'S' && value <= myHeight + 1 ) ||
				( ( myHeight == 'z' || myHeight == 'y' ) && value == 'E' ) ||  //'E' is same height as 'z'
				( myHeight == 'S' && ( value == 'a' || value == 'b' ) ) )      //'S' is same height as 'a'
			{
				result.push_back( loc );
			}
		}
	};

	CheckLocation( { pos.m_row - 1, pos.m_column } );
	CheckLocation( { pos.m_row + 1, pos.m_column } );
	CheckLocation( { pos.m_row, pos.m_column - 1 } );
	CheckLocation( { pos.m_row, pos.m_column + 1 } );

	return result;
}

void
Result::Process( const std::string& data )
{
	m_heightMap.push_back( data );
}

void
Result::Teardown( )
{
	m_heightMap.clear( );
}
