import distress_signal;

#include <string>

using distress_signal::Result;
using distress_signal::Extractor;
using distress_signal::Packet;

void
Result::Init()
{
	m_inRightOrder = 0;
}

void
Result::Teardown()
{
	m_packets.clear( );
}

void
Result::ProcessNewPacketData( const std::string& data )
{
	auto tokens = Extractor( data ).ExtractTokens( );
	m_packets.push_back( Packet( tokens ) );
}
