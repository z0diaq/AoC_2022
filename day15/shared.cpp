import beacon_exclusion_zone;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <regex>

//containers
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <array>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace beacon_exclusion_zone;

const std::regex g_lineMatcher( "Sensor at x=(\\-?\\d+), y=(\\-?\\d+): closest beacon is at x=(\\-?\\d+), y=(\\-?\\d+)" );

void
Result::Teardown()
{
	m_sensorsData.clear( );
}

void
Result::Process( const std::string& data )
{
	std::smatch lineParts;
	if( std::regex_match( data, lineParts, g_lineMatcher ) )
	{
		Point sensor( std::stoi( lineParts[ 1 ].str( ) ), std::stoi( lineParts[ 2 ].str( ) ) );
		Point beacon( std::stoi( lineParts[ 3 ].str( ) ), std::stoi( lineParts[ 4 ].str( ) ) );
		m_sensorsData.push_back( SensorInfo( sensor, beacon ) );
	}
}
