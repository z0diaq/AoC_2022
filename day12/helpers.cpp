import hill_climbing_algorithm;

#include <iostream>
#include <string>
#include <stdexcept>

#include <vector>
#include <deque>

using namespace hill_climbing_algorithm;

std::ostream&
operator<<( std::ostream& o, const Location& loc )
{
	o << "r=" << loc.m_row << " c=" << loc.m_column;
	return o;
}

bool
Result::IsValid( const Location& loc ) const
{
	return loc.m_row < m_heightMap.size( ) &&
		loc.m_column < m_heightMap.front( ).length( );
}

Location
Result::FindLocation( const char c ) const
{
	for( size_t rowNo = 0; rowNo != m_heightMap.size( ); ++rowNo )
	{
		const std::string& line = m_heightMap[ rowNo ];
		for( size_t columnNo = 0; columnNo != line.length( ); ++columnNo )
			if( line[ columnNo ] == c )
				return { rowNo, columnNo };
	}

	throw std::logic_error( "Could not find required location on map" );
}

const char
Result::Value( const Location& pos ) const
{
	return m_heightMap[ pos.m_row ][ pos.m_column ];
}
