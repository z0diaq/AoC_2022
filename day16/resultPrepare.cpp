import proboscidea_volcanium;

#include <string>

#include <vector>
#include <map>
#include <set>
#include <ranges>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/join.hpp>

using namespace proboscidea_volcanium;

void
Result::Teardown()
{
	m_valves.clear( );
	m_analyzedFlows.clear( );
	m_minDistances.Teardown( );
}

std::vector<Connection>
BuildConnections( const std::vector<std::string>& source )
{
	std::vector<Connection> result( source.size( ) - 10, Connection( "" ) );
	std::transform(
		source.begin( ) + 10,
		source.end( ),
		result.begin( ),
		[ ]( const std::string& connectionName ) -> Connection
		{
			return Connection( connectionName, 1 );
		} );
	return result;
}

void
Result::Process( const std::string& data )
{
	std::vector<std::string> tokens;
	boost::split( tokens, data, boost::is_any_of( " =;," ), boost::algorithm::token_compress_on );

	AddScanline( tokens[ 1 ],
		static_cast< unsigned >( std::stoi( tokens[ 5 ] ) ),
		BuildConnections( tokens ) );
}

void
Result::Prepare( )
{
	RemoveDummyValves( );
	m_minDistances.Init( m_valves );
}

void
Result::AddScanline( const std::string& name, unsigned int flowRate, const std::vector<Connection>& connections )
{
	m_valves[ name ] = ValveInfo( flowRate, connections );
}

void
Result::Remove( const std::string& name )
{
	const std::vector<Connection> connections = m_valves[ name ].Connections( );

	for( Connection const& connection : connections )
		m_valves[ connection.m_name ].RemoveConnection( name );

	m_valves.erase( name );
}

void
Result::Connect( const std::string& from, const std::string& to, const uint distance )
{
	m_valves[ from ].AddConnection( Connection( to, distance ) );
}

void
Result::CreateNewConnections( const std::vector<Connection>& connections )
{
	for( size_t fromIndex = 0; fromIndex != connections.size( )/*( connections.size( ) + 1 ) / 2*/; ++fromIndex )
	{
		const Connection& from = connections[ fromIndex ];
		for( const Connection& to : connections )
		{
			if( from.m_name == to.m_name )
				continue;
			Connect( from.m_name, to.m_name, from.m_distance + to.m_distance );
		}
	}
}

void
Result::RemoveDummyValves( )
{
	//too bad std::maps doesn't have 'keys' method
	auto keysView = std::views::keys( m_valves );
	//can't work on keysView directly since we are going to modify underlying map
	std::vector<std::string> valveNames{ keysView.begin( ), keysView.end( ) };

	for( const auto& name : valveNames )
	{
		if( false == m_valves[ name ].FlowRate( ) && name != "AA"/*start location - can't remove it*/ )
		{
			auto connections = m_valves[ name ].Connections( );

			Remove( name );
			CreateNewConnections( connections );
		}
	}

	SetIndexes( );
}

void
Result::SetIndexes( )
{
	uint index = 0;
	for( auto& valve : m_valves )
		valve.second.Index( index++ );
}
