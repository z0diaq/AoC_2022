import hill_climbing_algorithm;

#include <string>

using namespace hill_climbing_algorithm;

void
Result::ProcessTwo(const std::string& data)
{
	Process( data );
}

std::string
Result::FinishPartTwo()
{
	return std::to_string( FindShortestPathLength( ) );
}
