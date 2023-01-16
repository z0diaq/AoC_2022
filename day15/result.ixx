module;

#include <string>
#include <algorithm>
#include <vector>

export module beacon_exclusion_zone;
export import :sensor_info;
export import :scan;
export import :point;

import AoC;

export namespace beacon_exclusion_zone
{


	class Result : public AoC::Result
	{
	protected:

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data
		std::vector<SensorInfo> m_sensorsData;

		void Process( const std::string& data );

		std::vector<Range> FindRangesWithoutBeacons( int row ) const
		{
			std::vector<Range> result;
			for( const auto& sensorInfo : m_sensorsData )
			{
				int manhattanDistance = sensorInfo.Distance( );
				int noBeaconArea = manhattanDistance - std::abs( sensorInfo.m_sensor.m_y - row );
				if( noBeaconArea > 0 )
					result.push_back( Range( sensorInfo.m_sensor.m_x - noBeaconArea, sensorInfo.m_sensor.m_x + noBeaconArea ) );
			}
			return result;
		}

		void Simplify( std::vector<Range>& noBeacons ) const
		{
			if( noBeacons.empty( ) )
				return;

			std::vector<Range> result;
			bool madeChanges = false;

			do
			{
				madeChanges = false;
				std::sort( noBeacons.begin( ), noBeacons.end( ) );
				result.push_back( noBeacons.front( ) );
				for( size_t index = 1; index != noBeacons.size( ); ++index )
				{
					const Range& current = noBeacons[ index ];
					if( false == result.back( ).TryMerge( current ) )
						result.push_back( current );
					else
						madeChanges = true;
				}

				noBeacons.clear( );
				noBeacons.swap( result );
			} while( madeChanges );
		}

		int SumLocationsWithoutBeacons( const std::vector<Range>& noBeacons ) const
		{
			int result = 0;
			for( const auto& range : noBeacons )
				result += range.Size( );

			return result;
		}
	};
}
