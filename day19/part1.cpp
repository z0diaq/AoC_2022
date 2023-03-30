import not_enough_minerals;

#include <string>

using namespace not_enough_minerals;

void
Result::ProcessOne( const std::string& data )
{
	Process( data );
}

std::string
Result::FinishPartOne( )
{
	size_t result = 0;
	for( size_t blueprintNumber = 0; blueprintNumber != m_blueprints.size(); ++blueprintNumber )
		result += ( blueprintNumber + 1 ) * MostGeodesCollected( m_blueprints[ blueprintNumber ], 24 );

	return std::to_string( result );
}
