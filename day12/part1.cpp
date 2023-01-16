import hill_climbing_algorithm;

#include <string>

using namespace hill_climbing_algorithm;

void
Result::ProcessOne( const std::string& data )
{
	Process( data );
}

std::string
Result::FinishPartOne( )
{
	return std::to_string( FindShortestPathLength( ) );
}
