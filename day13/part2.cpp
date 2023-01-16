import distress_signal;

#include <string>
#include <algorithm>
#include <stdexcept>

using namespace distress_signal;

void
Result::ProcessTwo(const std::string& data )
{
	if( data.empty( ) )
		return;

	ProcessNewPacketData( data );
}

std::string
Result::FinishPartTwo()
{
	ProcessNewPacketData( "[[2]]" );
	Packet two = m_packets.back( );

	ProcessNewPacketData( "[[6]]" );
	Packet six = m_packets.back( );

	std::sort( m_packets.begin( ), m_packets.end( ) );

	auto twoPos = std::find_if( m_packets.begin( ), m_packets.end( ), [ &two ]( const Packet& packet ) -> bool
		{
			return two == packet;
		} );

	if( twoPos == m_packets.end( ) )
		throw std::logic_error( "Could not find packet [[2]]" );

	auto sixPos = std::find_if( twoPos, m_packets.end( ), [ &six ]( const Packet& packet ) -> bool
		{
			return six == packet;
		} );

	if( sixPos == m_packets.end( ) )
		throw std::logic_error( "Could not find packet [[6]]" );

	auto twoIndex = std::distance( m_packets.begin( ), twoPos ) + 1,
		sixIndex = std::distance( m_packets.begin( ), sixPos ) + 1;

	return std::to_string( twoIndex * sixIndex );
}
