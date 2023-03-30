module;

#include <bitset>

export module not_enough_minerals:blocked_robots;
import :types;

import AoC;


export namespace not_enough_minerals
{
	class BlockedRobots
	{
		std::bitset<4> m_blocked;

	public:

		void Block( Type type )
		{
			m_blocked.set( type );
		}

		bool IsBlocked( Type type ) const
		{
			return m_blocked.test( type );
		}

		void Reset( )
		{
			m_blocked.reset( );
		}
	};
}
