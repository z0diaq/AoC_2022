import regolith_reservoir;

#include <stdexcept>

using regolith_reservoir::Scan;

Scan::Scan( ) :
	m_rangeX( 500 ),
	m_rangeY( 0 )
{
}

void
Scan::Reset( )
{
	m_rangeX = Range( 500 );
	m_rangeY = Range( 0 );
	m_rawMap.clear( );
	m_areaScan.clear( );
	m_haveFloor = false;
}

char&
Scan::Get( const Point& pt )
{
	if( IsOutside( pt ) )
		throw std::logic_error( "Point is outside of range!" );
	return m_areaScan[ pt.m_y - m_rangeY.m_min ][ pt.m_x - m_rangeX.m_min ];
}

char
Scan::Get( const Point& pt ) const
{
	if( IsOutside( pt ) )
		throw std::logic_error( "Point is outside of range!" );
	return m_areaScan[ pt.m_y - m_rangeY.m_min ][ pt.m_x - m_rangeX.m_min ];
}
