import distress_signal;

#include <deque>
#include <string>

using distress_signal::Item;
using distress_signal::Packet;

Packet::Packet( std::deque<Item>& tokens )
{
	unsigned int number;

	while( false == tokens.empty( ) )
	{
		Item item = tokens.front( );
		tokens.pop_front( );

		if( item.IsNumber( number ) )
			m_subPackets.push_back( Packet( number ) );
		else if( item.IsListOpen( ) )
			m_subPackets.push_back( Packet( tokens ) );
		else if( item.IsListClose( ) )
			return;
	}
}

Packet::Packet( unsigned int value ) :
	m_value( value )
{
}

bool
Packet::HasValue( ) const
{
	return m_value.has_value( );
}

unsigned int
Packet::Value( ) const
{
	return m_value.value( );
}
