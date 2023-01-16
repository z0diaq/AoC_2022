import regolith_reservoir;

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

using namespace regolith_reservoir;

void
Result::ProcessTwo(const std::string& data )
{
	Process( data );
}

std::string
Result::FinishPartTwo()
{
	m_scan.BeforeCompute( true );
	unsigned int sandCount{ 0 };
	while( m_scan.DropSand( ) != DropResult::BlockedAtStart )
		++sandCount;

	return std::to_string( sandCount );
}
