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

Result::Result()
{

}

void
Result::Init()
{
	m_reg = 1;

	m_iteration = 1;
	m_result = 0;

	if( IsPartTwo( ) )
	{
		for( int i = 0; i != 6; ++i )
			m_screen.push_back( std::string( 40, '.' ) );
	}
}

void
Result::Teardown()
{
	m_screen.clear( );
}
