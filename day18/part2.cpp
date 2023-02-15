import boiling_boulders;

#include <string>

using namespace boiling_boulders;

void
Result::ProcessTwo(const std::string& data)
{
	Process( data );
}

std::string
Result::FinishPartTwo()
{
	return std::to_string( OutsideArea( ) - InsideArea( ) );
}

size_t
Result::InsideArea( ) const
{
	Cube minValue( 0, 0, 0 );
	Grid negativeImage = m_grid.NegativeImage( minValue );
	negativeImage.RemoveConnectedCubes( minValue );
	return negativeImage.ComputeOutsideArea( );
}
