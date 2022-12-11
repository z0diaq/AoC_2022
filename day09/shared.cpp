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

Result::Result()
{

}

void
Result::Init()
{
	//m_head = m_tail = { 0, 0 };
	if( IsPartOne( ) )
	{
		m_knots.push_back( { 0, 0 } );
		m_knots.push_back( { 0, 0 } );
	}
	else
	{
		for( int i = 0; i != 10; ++i )
			m_knots.push_back( { 0, 0 } );
	}

	CheckTail( m_knots.back( ) );
}

void
Result::Teardown()
{
	m_knots.clear( );
	m_visitedPoints.clear( );
}


std::ostream&
rope_bridge::operator<<( std::ostream& o, const Position& pos )
{
	o << "(" << pos.first << "," << pos.second << ")";
	return o;
}