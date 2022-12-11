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
Result::ProcessOne( const std::string& data )
{
	char direction = data[ 0 ];
	int distance = boost::lexical_cast< int >( data.substr( 2 ) );
	;// std::cout << "dir:" << direction << ", dist : " << distance << std::endl;

	Position moveVector{ 0,0 };

	switch( direction )
	{
	case 'R':
		moveVector.first = 1;
		break;
	case 'L':
		moveVector.first = -1;
		break;
	case 'U':
		moveVector.second = -1;
		break;
	case 'D':
		moveVector.second = 1;
		break;
	}

	while( distance )
	{
		m_knots.front( ).first += moveVector.first;
		m_knots.front( ).second += moveVector.second;

		;// std::cout << "\thead:" << m_head << std::endl;
		--distance;
		
		
		//if( MoveTail( m_knots.front( ), m_knots.back( ) ) )
		//	CheckTail( m_knots.back( ) );

		for( size_t no = 1; no < m_knots.size( ); ++no )
		{
			if( false == MoveTail( m_knots[ no - 1 ], m_knots[ no ] ) )
				break;
		}
		CheckTail( m_knots.back( ) );
	}

	static int moves = 0;

	if( moves > 0 )
	{
		std::cout << std::endl << std::endl;
		DumpVisitedPoints( );
		moves = 0;
	}
}

int
Normalize( int val )
{
	if( std::abs( val ) > 1 )
		val = val / std::abs( val );
	return val;
}

bool
Result::MoveTail( const Position& head, Position& tail ) const
{
	//direction to head?

	Position direction{ head.first - tail.first, head.second - tail.second };
	if( std::abs( direction.first ) <= 1 && std::abs( direction.second ) <= 1 )
	{
		;// std::cout << "\t\ttail less than 1 away from head - nothing todo - head:" << m_head << ", tail:" << m_tail << std::endl;
		return false;
	}
	else
	{
		//if( std::abs( direction.first ) + std::abs( direction.second ) > 3 )
		//	throw std::logic_error( "distance too high" );

		//need to get in line right after head
		if( std::abs( direction.first ) > std::abs( direction.second ) )
			direction.second = 0;
		else
		{
			if( std::abs( direction.first ) != std::abs( direction.second ) )
				direction.first = 0;
			//if both are same then move diagonally
		}

		//normalize movement to 1 vector
		Position newTail{
			head.first - Normalize( direction.first ),
			head.second - Normalize( direction.second ) };
		;// std::cout << "\t\ttail moved from " << m_tail << " to " << newTail << std::endl;
		tail = newTail;

		return true;
	}

}

void
Result::CheckTail( const Position& tail )
{
	// y => x
	m_visitedPoints[ tail.second ].insert( tail.first );
}

std::string
Result::FinishPartOne( )
{
	size_t sum = 0;
	for( auto it : m_visitedPoints )
		sum += it.second.size( );

	DumpVisitedPoints( );

	//6054 too high

	return std::to_string( sum );
}

void
Result::DumpVisitedPoints( )
{
	int minX = 0,
		maxX = 0,
		minY = 0,
		maxY = 0;
	for( auto it : m_visitedPoints )
	{
		minY = std::min( it.first, minY );
		maxY = std::max( it.first, maxY );

		for( auto x : it.second )
		{
			minX = std::min( x, minX );
			maxX = std::max( x, maxX );
		}
	}

	std::cout << "visited points:" << std::endl;
	for( int y = minY; y <= maxY; ++y )
	{
		const auto& values = m_visitedPoints[ y ];

		for( int x = minX; x <= maxX; ++x )
		{
			if( values.contains( x ) )
				std::cout << "#";
			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}
}
