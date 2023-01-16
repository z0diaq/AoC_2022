module;

#include <cstdlib> //abs

export module beacon_exclusion_zone:point;

export namespace beacon_exclusion_zone
{

	struct Point
	{
		int m_x;
		int m_y;

		Point( int x, int y ) :
			m_x( x ),
			m_y( y )
		{

		}

		int ManhattanDistance( const Point& rhs ) const
		{
			return std::abs( m_x - rhs.m_x ) + std::abs( m_y - rhs.m_y );
		}
	};
}
