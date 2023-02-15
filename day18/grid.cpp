module;

#include <deque>

module boiling_boulders:grid;
import :cube;

using boiling_boulders::Grid;
using boiling_boulders::Cube;

void
Grid::Add( const Cube& newCube )
{
	m_droplets.insert( newCube );
}

void
Grid::Reset( )
{
	m_droplets.clear( );
}

size_t
Grid::NeighboursCount( const Cube& cube ) const
{
	size_t result{ 0 };

	auto neighbours = cube.PossibleNeighbours( );
	for( const auto& neighbour : neighbours )
		result += m_droplets.count( neighbour );

	return result;
}

size_t
Grid::ComputeOutsideArea( ) const
{
	size_t result{ 0 };

	for( const auto& cube : m_droplets )
		result += ( 6 - NeighboursCount( cube ) );

	return result;
}

std::pair<Cube, Cube>
Grid::FindContainingBox( int extraSpace /*= 1*/ ) const
{
	constexpr int minValue = std::numeric_limits<int>::min( ),
		maxValue = std::numeric_limits<int>::max( );
	Cube fromRange( maxValue, maxValue, maxValue ), toRange( minValue, minValue, minValue );

	for( const auto& cube : m_droplets )
	{
		fromRange.UpdateIfSmaller( cube );
		toRange.UpdateIfBigger( cube );
	}

	return std::make_pair(
		Cube( fromRange.X( ) - extraSpace, fromRange.Y( ) - extraSpace, fromRange.Z( ) - extraSpace ),
		Cube( toRange.X( ) + extraSpace  , toRange.Y( ) + extraSpace  , toRange.Z( ) + extraSpace ) );
}

Grid
Grid::NegativeImage( Cube& minValue ) const
{
	auto containingBox = FindContainingBox( );
	Grid result;

	minValue = containingBox.first;

	for( int x = containingBox.first.X( ); x != containingBox.second.X( ); ++x )
	{
		for( int y = containingBox.first.Y( ); y != containingBox.second.Y( ); ++y )
		{
			for( int z = containingBox.first.Z( ); z != containingBox.second.Z( ); ++z )
			{
				Cube cube( x, y, z );
				if( 0 == m_droplets.count( cube ) )
					result.Add( cube );
			}
		}
	}

	return result;
}

void
Grid::RemoveConnectedCubes( const Cube& cube )
{
	std::deque<Cube> purgeList{ cube };
	m_droplets.erase( cube );

	while( false == purgeList.empty( ) )
	{
		auto purgeItem = purgeList.front( );
		purgeList.pop_front( );

		auto neighbours = purgeItem.PossibleNeighbours( );
		for( const auto& neighbour : neighbours )
			if( m_droplets.erase( neighbour ) )
				purgeList.push_back( neighbour );
	}
}
