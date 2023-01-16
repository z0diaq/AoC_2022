import regolith_reservoir;

#include <string>
#include <stdexcept>

using regolith_reservoir::Scan;
using regolith_reservoir::Point;

void
Scan::Process( const std::vector<Point>& path )
{
	for( size_t index = 1; index != path.size( ); ++index )
		BlockPath( path[ index - 1 ], path[ index ] );
}

void
Scan::SetRock( const Point& pt )
{
	Get( pt ) = ROCK;
}

void
Scan::BeforeCompute( bool addInifiniteFloor /*= false*/ )
{
	if( addInifiniteFloor )
	{
		m_rangeY.m_max += 2;
		m_floorLevel = m_rangeY.m_max;
		m_haveFloor = true;

		//prepare space for all sand moving to sides
		int height = m_rangeY.Length( ) + 1;
		m_rangeX.m_min -= height;
		m_rangeX.m_max += height;
	}

	const int width = m_rangeX.Length( ) + 1;
	int height = m_rangeY.Length( ) + 1;

	std::string emptyLine( width, AIR );
	while( height-- )
		m_areaScan.push_back( emptyLine );

	for( auto rowIt = m_rawMap.begin( ); rowIt != m_rawMap.end( ); ++rowIt )
	{
		const int row = rowIt->first;

		const auto& points = rowIt->second;
		for( int column : points )
			SetRock( Point{ column, row } );
	}
}

void
Scan::BlockPath( Point from, Point to )
{
	m_rangeX.Update( from.m_x );
	m_rangeX.Update( to.m_x );
	m_rangeY.Update( from.m_y );
	m_rangeY.Update( to.m_y );

	if( from.m_x != to.m_x && from.m_y != to.m_y )
		throw std::logic_error( "Expecting not to have diagonal lines!" );

	if( to.m_x < from.m_x )
		std::swap( to.m_x, from.m_x );

	if( to.m_y < from.m_y )
		std::swap( to.m_y, from.m_y );

	if( to.m_x > from.m_x )
	{
		for( int x = from.m_x; x <= to.m_x; ++x )
		{
			m_rawMap[ to.m_y ].insert( x );
		}
	}
	else
	{
		for( int y = from.m_y; y <= to.m_y; ++y )
		{
			m_rawMap[ y ].insert( from.m_x );
		}
	}
}
