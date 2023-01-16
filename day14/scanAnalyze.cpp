import regolith_reservoir;

#include <string>
#include <stdexcept>

using regolith_reservoir::Scan;
using regolith_reservoir::DropResult;
using regolith_reservoir::Point;

void
Scan::RestSand( const Point& pt )
{
	auto& ref = Get( pt );
	if( ref != AIR )
		throw std::logic_error( "Already taken!" );
	ref = SAND;
}

bool
Scan::IsOutside( const Point& pt ) const
{
	return m_rangeX.IsOutside( pt.m_x ) || m_rangeY.IsOutside( pt.m_y );
}

bool
Scan::IsFree( const Point& pt ) const
{
	return Get( pt ) == AIR && false == ( m_haveFloor && pt.m_y == m_floorLevel );
}

DropResult
Scan::DropSand( )
{
	static const Point start{ 500, 0 };
	Point pt{ 500, 0 };

	auto CheckPos = [ &pt, this ]( short diffX, short diffY, DropResult& dropResult ) -> bool
	{
		Point temp{ pt.m_x + diffX, pt.m_y + diffY };

		if( IsOutside( temp ) )
		{
			dropResult = DropResult::FallenIntoAbyss;
			return false;
		}

		if( IsFree( temp ) )
		{
			pt = temp;
			dropResult = DropResult::FoundRestingPlace;
			return true;
		}

		dropResult = DropResult::Blocked;
		return false;
	};

	while( true )
	{
		DropResult dropResult = DropResult::Unknown;
		const bool moveResult = CheckPos( 0, 1, dropResult ) || CheckPos( -1, 1, dropResult ) || CheckPos( 1, 1, dropResult );
		if( moveResult )
			continue;

		if( dropResult == DropResult::Blocked )
		{
			if( pt == start && false == IsFree( pt ) )
				return DropResult::BlockedAtStart;
			RestSand( pt );

			if( IsOutside( Point{ pt.m_x - 1, pt.m_y } ) || IsOutside( Point{ pt.m_x + 1, pt.m_y } ) )
				return DropResult::FallenIntoAbyss;
			return DropResult::FoundRestingPlace;
		}

		return DropResult::FallenIntoAbyss;
	}
}
