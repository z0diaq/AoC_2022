import boiling_boulders;

#include <string>

using namespace boiling_boulders;

void
Result::ProcessOne( const std::string& data )
{
	Process( data );
}

std::string
Result::FinishPartOne( )
{
	return std::to_string( OutsideArea( ) );
}
