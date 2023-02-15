import boiling_boulders;

#include <string>

using namespace boiling_boulders;

void
Result::Process( const std::string& data )
{
	m_grid.Add( Cube( data ) );
}

size_t
Result::OutsideArea( ) const
{
	return m_grid.ComputeOutsideArea( );
}

void
Result::Teardown()
{
	m_grid.Reset( );
}
