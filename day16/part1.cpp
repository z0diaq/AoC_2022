import proboscidea_volcanium;

#include <string>
#include <set>
#include <ranges>

using namespace proboscidea_volcanium;

void
Result::ProcessOne( const std::string& data )
{
	Process( data );
}

std::string
Result::FinishPartOne( )
{
	Prepare( );

	const std::string startingPoint{ "AA" };
	const uint remainingTime{ 30 };

	const uint result = ComputeBestCumulativeFlow(
		startingPoint,
		std::set<std::string>(
			std::views::keys( m_valves ).begin( ),
			std::views::keys( m_valves ).end( ) ),
		remainingTime );

	return std::to_string( result );
}
