module;

#include <string>
#include <vector>
#include <stdexcept>

export module proboscidea_volcanium:valve_info;

import AoC;

export namespace proboscidea_volcanium
{
	typedef unsigned int uint;

	struct Connection
	{
		std::string m_name;
		uint m_distance = 1;

		Connection( ) = default;
		Connection( const std::string& name, const uint distance = 1 ) :
			m_name( name ),
			m_distance( distance )
		{

		}
	};


	class ValveInfo
	{
		uint m_flowRate = 0;
		uint m_index = 0;
		std::vector<Connection> m_connections;
	public:
		ValveInfo( ) = default;

		ValveInfo( uint flowRate, const std::vector<Connection>& connections ) :
			m_flowRate( flowRate ),
			m_connections( connections )
		{

		}

		uint FlowRate( ) const
		{
			return m_flowRate;
		}

		const std::vector<Connection>& Connections( ) const
		{
			return m_connections;
		}

		void RemoveConnection( const std::string& name )
		{
			for( auto it = m_connections.begin( ); it != m_connections.end( ); ++it )
			{
				if( it->m_name == name )
				{
					m_connections.erase( it );
					return;
				}
			}

			throw std::logic_error( "Connection for remove not found!" );
		}

		void AddConnection( const Connection& connection )
		{
			m_connections.push_back( connection );
		}

		uint Index( ) const
		{
			return m_index;
		}

		void Index( const uint index )
		{
			m_index = index;
		}
	};
}
