import beacon_exclusion_zone;

#include <string>

using namespace beacon_exclusion_zone;

void
Result::ProcessTwo(const std::string& data )
{
	Process( data );
}

std::string
Result::FinishPartTwo( )
{
	uint64_t result = 0;
	const Range searchArea( 0, 4'000'000 );

	for( int row = searchArea.m_min; row != searchArea.m_max; ++row )
	{
		auto noBeacons = FindRangesWithoutBeacons( row );
		Simplify( noBeacons );
		if( noBeacons.size( ) > 1 )
		{
			result = static_cast< uint64_t>( ( noBeacons.front( ).m_max + 1 )) * static_cast< uint64_t>( searchArea.m_max ) + row;
			break;
		}
	}

	return std::to_string( result );
}
