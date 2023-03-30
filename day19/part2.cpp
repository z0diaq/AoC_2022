import not_enough_minerals;

#include <string>

using namespace not_enough_minerals;

void
Result::ProcessTwo(const std::string& data)
{
	Process( data );
}

std::string
Result::FinishPartTwo()
{
	size_t result = 1;

	for( size_t no = 0; no != std::min( m_blueprints.size( ), 3ull ); ++no )
		result *= MostGeodesCollected( m_blueprints[ no ], 32 );

	return std::to_string( result );
}
