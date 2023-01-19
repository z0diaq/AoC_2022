module;

#include <algorithm>
#include <string>

#include <iostream>

module pyroclastic_flow:rocks_tower;
import :rock;
import :rock_shape;

using namespace pyroclastic_flow;

void
RocksTower::PrepareForNewRock( const Rock& rock )
{
	m_scan.resize( std::max(
		m_scan.size( ),
		rock.Top( ) ),
		std::string( s_chamberWidth, '.' ) );
}

size_t
RocksTower::Height( ) const
{
	return m_currentHeight;
}

bool
RocksTower::IsUsed( size_t xOffset, size_t yOffset ) const
{
	return m_scan[ yOffset ][ xOffset ] == '#';
}

bool
RocksTower::RestRock( size_t xOffset, size_t yOffset )
{
	if( IsUsed( xOffset, yOffset ) )
		return false;
	m_scan[ yOffset ][ xOffset ] = '#';
	m_currentHeight = std::max( m_currentHeight, yOffset );

	return true;
}

bool
RocksTower::TryBuildHash( size_t& hash, const size_t range )
{
	if( m_currentHeight < range )
		return false;

	std::string result;
	result.reserve( range * 7 );
	for( size_t rowNo = m_currentHeight - range; rowNo <= m_currentHeight; ++rowNo )
		result.append( m_scan[ rowNo ] );

	hash = std::hash<std::string>{}( result );

	return true;
}