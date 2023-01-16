module;

#include <string>
#include <vector>
#include <map>

export module proboscidea_volcanium:min_distances;
export import :valve_info;

import AoC;

export namespace proboscidea_volcanium
{
	struct MinDistances
	{
		uint              m_count = 0;
		std::vector<uint> m_values;

		void Init( const std::map<std::string, ValveInfo>& valves )
		{
			m_count = static_cast< uint >( valves.size( ) );
			m_values.resize( m_count * m_count, std::numeric_limits<uint>::max( ) / 2/*half so we can use in sum testing*/ );

			FloydWarshall( valves );
		}

		uint Index( const uint from, const uint to ) const
		{
			return to * m_count + from;
		}

		void Teardown( )
		{
			m_count = 0;
			m_values.clear( );
		}

		uint& Distance( const uint from, const uint to )
		{
			return m_values[ Index( from, to ) ];
		}

		uint Distance( const uint from, const uint to ) const
		{
			return m_values[ Index( from, to ) ];
		}

		void
			FloydWarshall( const std::map<std::string, ValveInfo>& valves )
		{
			for( auto it : valves )
			{
				for( const auto& connection : it.second.Connections( ) )
					Distance( it.second.Index( ), valves.at( connection.m_name ).Index( ) ) = connection.m_distance;
			}

			for( uint index = 0; index != m_count; ++index )
				Distance( index, index ) = 0;

			for( uint k = 0; k != m_count; ++k )
				for( uint i = 0; i != m_count; ++i )
					for( uint j = 0; j != m_count; ++j )
						Distance( i, j ) = std::min( Distance( i, j ), Distance( i, k ) + Distance( k, j ) );
		}
	};
}
