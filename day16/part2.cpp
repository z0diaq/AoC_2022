import proboscidea_volcanium;

#include <string>

#include <vector>
#include <set>
#include <ranges>

using namespace proboscidea_volcanium;

void
Result::ProcessTwo(const std::string& data )
{
	Process( data );
}

std::string
Result::FinishPartTwo()
{
	Prepare( );

	const std::string startingValve{ "AA" };
	const uint remainingTime{ 26 };

	std::vector<std::string> allKeys(
		std::views::keys( m_valves ).begin( ),
		std::views::keys( m_valves ).end( ) );

	//use bits to distribute each valve to either me or elephant in all possible combinations
	std::uint64_t last = 1ull << m_valves.size( );

	uint bestFlow = 0;
	for( std::uint64_t combination = 0; combination != last; ++combination )
	{
		std::set<std::string> valvesForMe{ startingValve }, valvesForElephant{ startingValve };

		for( std::uint64_t bit = 1/*starting point already added so take from second on list*/; bit < m_valves.size( ); ++bit )
		{
			if( ( 1ull << bit ) & combination )
				valvesForMe.insert( allKeys[ bit ] );
			else
				valvesForElephant.insert( allKeys[ bit ] );
		}

		bestFlow = std::max(
			bestFlow,
			ComputeBestCumulativeFlow(
				startingValve,
				valvesForMe,
				remainingTime ) +
			ComputeBestCumulativeFlow(
				startingValve,
				valvesForElephant,
				remainingTime ) );
	}

	return std::to_string( bestFlow );
}
