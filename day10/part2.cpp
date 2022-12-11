import cathode_ray_tube;

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

using namespace cathode_ray_tube;

void
Result::ProcessTwo(const std::string& data)
{
	ProcessOne( data );
}

std::string
Result::FinishPartTwo()
{
	std::cout << "result" << std::endl;

	for( const auto& line : m_screen )
		std::cout << line << std::endl;


	std::string result = m_screen[ 0 ];
	for( int i = 1; i != m_screen.size( ); ++i )
	{
		result += "\r\n";
		result += m_screen[ i ];
	}

	return result;
}
