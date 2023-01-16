import regolith_reservoir;

#include <string>

using namespace regolith_reservoir;

void
Result::ProcessOne( const std::string& data )
{
	Process( data );
}

std::string
Result::FinishPartOne( )
{
	m_scan.BeforeCompute( );
	unsigned int sandCount{ 0 };
	while( m_scan.DropSand( ) != DropResult::FallenIntoAbyss )
		++sandCount;

	return std::to_string( sandCount );
}


