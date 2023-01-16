import distress_signal;

#include <string>

using namespace distress_signal;

void
Result::ProcessOne( const std::string& data )
{
	if( data.empty( ) )
		return;

	ProcessNewPacketData( data );

	const size_t numPackets = m_packets.size( );
	if( numPackets % 2 == 0 )
	{
		const bool inRightOrder = m_packets[ numPackets - 2 ] < m_packets[ numPackets - 1 ];
		if( inRightOrder )
		{
			m_inRightOrder += ( numPackets + 1 ) / 2;//size => packet pair index
		}
	}
}

std::string
Result::FinishPartOne( )
{
	return std::to_string( m_inRightOrder );
}
