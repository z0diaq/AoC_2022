import distress_signal;

#include <deque>

using distress_signal::Item;
using distress_signal::Packet;

distress_signal::Order
distress_signal::Compare( const Packet& lhs, const Packet& rhs )
{
	if( lhs.HasValue( ) && rhs.HasValue( ) )
	{
		if( lhs.Value( ) < rhs.Value( ) )
			return Order::Right;
		else if( lhs.Value( ) > rhs.Value( ) )
			return Order::Wrong;

		return Order::Inconclusive;
	}

	if( false == lhs.m_subPackets.empty( ) && false == rhs.m_subPackets.empty( ) )
	{
		size_t index = 0;
		for( ; index < lhs.m_subPackets.size( ) && index < rhs.m_subPackets.size( ); ++index )
		{
			auto subCompareResult = Compare( lhs.m_subPackets[ index ], rhs.m_subPackets[ index ] );
			if( subCompareResult != Order::Inconclusive )
				return subCompareResult;
		}

		//any of sides still have values ?
		if( lhs.m_subPackets.size( ) != rhs.m_subPackets.size( ) )
			return index == lhs.m_subPackets.size( ) ? Order::Right : Order::Wrong;//left run out of itmes first
	}
	else
	{
		if( lhs.HasValue( ) )
		{
			Packet temp;
			temp.m_subPackets.push_back( Packet( lhs.Value( ) ) );

			return Compare( temp, rhs );
		}
		else if( rhs.HasValue( ) )
		{
			Packet temp;
			temp.m_subPackets.push_back( Packet( rhs.Value( ) ) );

			return Compare( lhs, temp );
		}
		else
		{
			//one of side does not have values
			if( lhs.m_subPackets.empty( ) && false == rhs.m_subPackets.empty( ) )
				return Order::Right;
			else if( false == lhs.m_subPackets.empty( ) && rhs.m_subPackets.empty( ) )
				return Order::Wrong;
		}
	}

	return Order::Inconclusive;
}

bool
distress_signal::operator<( const Packet& lhs, const Packet& rhs )
{
	return Compare( lhs, rhs ) == Order::Right;
}

bool
distress_signal::operator==( const Packet& lhs, const Packet& rhs )
{
	return Compare( lhs, rhs ) == Order::Inconclusive;
}
