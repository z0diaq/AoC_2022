import rope_bridge;

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

using namespace rope_bridge;

void
Result::ProcessTwo(const std::string& data)
{
	ProcessOne( data );
}

std::string
Result::FinishPartTwo()
{

	//2375 - too low


	return FinishPartOne( );
	//return std::to_string(0);
}