import monkey_in_the_middle;

#include <iostream>
#include <string>

using namespace monkey_in_the_middle;

void
Result::ProcessTwo(const std::string& data)
{
	ProcessOne( data );
}

std::string
Result::FinishPartTwo()
{
	return FinishCommon( 10'000 );
}