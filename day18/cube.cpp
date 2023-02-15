module;

#include <string>
#include <stdexcept>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

module boiling_boulders:cube;

using boiling_boulders::Cube;

Cube::Cube( const std::string& row )
{
	std::vector<std::string> parts;

	boost::split( parts, row, boost::is_any_of( "," ) );

	if( parts.size( ) != 3 )
		throw std::logic_error( "Unexpected count of items" );

	m_x = std::stoi( parts[ 0 ] );
	m_y = std::stoi( parts[ 1 ] );
	m_z = std::stoi( parts[ 2 ] );
}

Cube::Cube( int x, int y, int z ) :
	m_x( x ),
	m_y( y ),
	m_z( z )
{

}

std::vector<Cube>
Cube::PossibleNeighbours( ) const
{
	std::vector<Cube> result;

	if( m_x > 0 )
		result.push_back( Cube( m_x - 1, m_y, m_z ) );
	result.push_back( Cube( m_x + 1, m_y, m_z ) );

	if( m_y > 0 )
		result.push_back( Cube( m_x, m_y - 1, m_z ) );
	result.push_back( Cube( m_x, m_y + 1, m_z ) );

	if( m_z > 0 )
		result.push_back( Cube( m_x, m_y, m_z - 1 ) );
	result.push_back( Cube( m_x, m_y, m_z + 1 ) );

	return result;
}

void
Cube::UpdateIfSmaller( const Cube & rhs )
{
	m_x = std::min( m_x, rhs.m_x );
	m_y = std::min( m_y, rhs.m_y );
	m_z = std::min( m_z, rhs.m_z );
}

void
Cube::UpdateIfBigger( const Cube & rhs )
{
	m_x = std::max( m_x, rhs.m_x );
	m_y = std::max( m_y, rhs.m_y );
	m_z = std::max( m_z, rhs.m_z );
}

bool
boiling_boulders::operator<( const Cube& lhs, const Cube& rhs )
{
	if( lhs.X( ) != rhs.X( ) )
		return lhs.X( ) < rhs.X( );

	if( lhs.Y( ) != rhs.Y( ) )
		return lhs.Y( ) < rhs.Y( );

	return lhs.Z( ) < rhs.Z( );
}
