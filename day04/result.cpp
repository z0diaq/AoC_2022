import camp_cleanup;

#include <iostream>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace camp_cleanup;

struct Range
{
	uint32_t m_start;
	uint32_t m_end;

	Range( ) :
		m_start( 0 ),
		m_end( 0 )
	{
	}

	Range( const std::string& start, const std::string& end )
	{
		m_start = boost::lexical_cast< uint32_t >( start );
		m_end = boost::lexical_cast< uint32_t >( end );
	}

	const bool operator<( const Range& rhs )
	{
		uint32_t diffA = this->m_end - this->m_start;
		uint32_t diffB = rhs.m_end - rhs.m_start;

		if( diffA > diffB )
			return false;

		if( diffA == diffB )
		{
			return this->m_start < rhs.m_start;
		}

		return true;
	}

	void Swap( Range& rhs )
	{
		std::swap( this->m_start, rhs.m_start );
		std::swap( this->m_end, rhs.m_end );
	}

	bool ContainedIn( const Range& rhs ) const
	{
		return this->m_start >= rhs.m_start && this->m_end <= rhs.m_end;
	}

	bool Intersects( const Range& rhs ) const
	{
		return ( this->m_start >= rhs.m_start && this->m_start <= rhs.m_end ) ||
			( this->m_end >= rhs.m_start && this->m_end <= rhs.m_end );
	}
};

void
ExtractRangesAndSort( const std::string& line, Range& elfA, Range& elfB );

void
Result::ProcessOne( const std::string& data )
{
	Range elfA, elfB;
	ExtractRangesAndSort( data, elfA, elfB );

	if( elfA.ContainedIn( elfB ) )
		++m_result;
}

void
Result::ProcessTwo( const std::string& data )
{
	Range elfA, elfB;
	ExtractRangesAndSort( data, elfA, elfB );

	if( elfA.Intersects( elfB ) )
		++m_result;
}

void
ExtractRangesAndSort( const std::string& line, Range& elfA, Range& elfB )
{
	std::vector<std::string> parts;
	boost::split( parts, line, boost::is_any_of( "-," ) );

	if( parts.size( ) != 4 )
		throw std::logic_error( "Expected to have 4 numbers here!" );

	elfA = { parts[ 0 ], parts[ 1 ] };
	elfB = { parts[ 2 ], parts[ 3 ] };

	if( elfB < elfA )
		elfA.Swap( elfB );
}