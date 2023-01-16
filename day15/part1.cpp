import beacon_exclusion_zone;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

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

void
Result::ProcessOne( const std::string& data )
{
	Process( data );
}

std::string
Result::FinishPartOne( )
{
	auto noBeacons = FindRangesWithoutBeacons( IsTestData( ) ? 10 : 2'000'000 );
	Simplify( noBeacons );

	return std::to_string( SumLocationsWithoutBeacons( noBeacons ) );
}
