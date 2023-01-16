module;

#include <vector>
#include <optional>
#include <deque>

export module distress_signal:packet;

export import :item;

export namespace distress_signal
{
	enum class Order
	{
		Right,
		Inconclusive,
		Wrong
	};

	struct Packet
	{
		std::vector<Packet>         m_subPackets;
		std::optional<unsigned int> m_value;

		Packet( ) = default;

		Packet( std::deque<Item>& tokens );

		Packet( unsigned int value );

		bool
		HasValue( ) const;

		unsigned int
		Value( ) const;

		static Packet
		Parse( );
	};

	Order
	Compare( const Packet& lhs, const Packet& rhs );

	bool operator<( const Packet& lhs, const Packet& rhs );
	bool operator==( const Packet& lhs, const Packet& rhs );
}
