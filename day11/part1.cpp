import monkey_in_the_middle;

#include <iostream>
#include <string>

using namespace monkey_in_the_middle;

void
Result::ProcessOne( const std::string& data )
{
	if( data.substr( 0, 6 ) == "Monkey" )
	{
		auto count = m_monkeys.size( );
		m_monkeys[ count ] = Monkey( );
		m_currentMonkey = &m_monkeys[ count ];
	}
	else
		m_currentMonkey->ParseLine( data );
}

std::string
Result::FinishPartOne( )
{
	return FinishCommon( 20 );
}
