import regolith_reservoir;

#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

using namespace regolith_reservoir;

void
Result::Process( const std::string& data )
{
	std::vector<std::string> path, numbers;
	boost::split( path,
		data,
		boost::is_any_of( " -> " ),
		boost::algorithm::token_compress_on );

	std::vector<Point> points;
	for( size_t index = 0; index != path.size( ); ++index )
	{
		const auto& node = path[ index ];
		boost::split( numbers, node, boost::is_any_of( "," ) );
		if( numbers.size( ) != 2 )
			throw std::logic_error( "Expecting exactly two numbers" );


		const int x = boost::lexical_cast< int >( numbers[ 0 ] ),
			y = boost::lexical_cast< int >( numbers[ 1 ] );

		points.push_back( Point{ x, y } );

	}

	m_scan.Process( points );
}

void
Result::Teardown()
{
	m_scan.Reset( );
}
