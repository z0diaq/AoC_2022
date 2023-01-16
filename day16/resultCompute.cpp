import proboscidea_volcanium;

#include <string>
#include <set>

#include <boost/algorithm/string/join.hpp>

using namespace proboscidea_volcanium;

static std::string
BuildId( uint timeValue, const std::string& name, const std::set<std::string>& names );

uint
Result::Index( const std::string& name ) const
{
	return m_valves.at( name ).Index( );
}

uint
Result::Distance( const std::string& from, const std::string& to ) const
{
	return m_minDistances.Distance( Index( from ), Index( to ) );
}

uint
Result::ComputeBestCumulativeFlow( const std::string& currentLocation, std::set<std::string> availableValves, const uint remainingTime )
{
	uint bestSubFlow = 0;
	for( const auto& availableValve : availableValves )
	{
		const uint distance = Distance( currentLocation, availableValve );

		if( distance + 1 <= remainingTime )
		{
			std::set<std::string> newAvailableValves( availableValves );
			newAvailableValves.erase( availableValve );

			const std::string id = BuildId( remainingTime - ( distance + 1 ), availableValve, newAvailableValves );

			if( m_analyzedFlows.count( id ) == 0 )
				m_analyzedFlows[ id ] = ComputeBestCumulativeFlow( availableValve, newAvailableValves, remainingTime - distance - 1 );

			bestSubFlow = std::max( bestSubFlow, m_analyzedFlows.at( id ) );
		}
	}

	return m_valves[ currentLocation ].FlowRate( ) * remainingTime + bestSubFlow;
}

static std::string
BuildId( const uint timeValue, const std::string& name, const std::set<std::string>& names )
{
	return
		std::to_string( timeValue )
		+ "-"
		+ name
		+ "-"
		+ boost::join( names, "-" );
}
