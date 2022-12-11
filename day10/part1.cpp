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
Result::ProcessOne( const std::string& data )
{
	CheckIteration( );
	if( data.substr( 0, 4 ) == "addx" )
	{
		int change = boost::lexical_cast< int >( data.substr( 5 ) );
		std::cout << "\t" << data << " >> add:" << change << std::endl;

		++m_iteration;
		CheckIteration( );

		m_reg += change;
		++m_iteration;
	}
	else
	{
		std::cout << "noop" << std::endl;

		++m_iteration;
		//CheckIteration( );
	}
}

std::string
Result::FinishPartOne( )
{
	return std::to_string( m_result );
}

bool
InRange( int cycle, int value );

void
Result::CheckIteration( )
{
	std::cout << " it:" << m_iteration << " value:" << m_reg << std::endl;
	if( ( m_iteration + 20 ) % 40 == 0 )
	{
		std::cout << "###### iteration " << m_iteration << " current value:" << m_reg << std::endl;
		m_result += m_iteration * m_reg;
	}

	if( IsPartTwo( ) )
	{
		if( InRange( ( m_iteration - 1 ) % 40, m_reg ) )
		{
			m_screen[ ( m_iteration - 1 ) / 40 ][ (m_iteration - 1) % 40 ] = '#';
		}
	}
}

bool
InRange( int cycle, int value )
{
	return cycle >= value - 1 && cycle <= value + 1;
}
