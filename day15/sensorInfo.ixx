module;

#include <string>
#include <algorithm>
#include <vector>

export module beacon_exclusion_zone:sensor_info;
export import :point;

export namespace beacon_exclusion_zone
{

	struct SensorInfo
	{
		Point m_sensor;
		Point m_beacon;
		int m_distance;

		SensorInfo( const Point& sensor, const Point& beacon ) :
			m_sensor( sensor ),
			m_beacon( beacon ),
			m_distance( sensor.ManhattanDistance( beacon ) )
		{

		}

		int Distance( ) const { return m_distance; }
	};
}