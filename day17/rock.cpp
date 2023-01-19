module;

#include <vector>
#include <string>
#include <stdexcept>

module pyroclastic_flow:rock;
import :rock_shape;
import :rocks_tower;

using namespace pyroclastic_flow;

Rock::Rock( const RockShape& shape, const size_t yOffset ) :
	m_shape( shape ),
	m_xOffset( 2 ),
	m_yOffset( yOffset )
{
}

void
Rock::TryMoveLeft( const RocksTower& tower )
{
	if( m_xOffset && false == m_shape.HasCollision( m_xOffset - 1, m_yOffset, tower ) )
		--m_xOffset;
}

void
Rock::TryMoveRight( const RocksTower& tower )
{
	if( ( m_xOffset + m_shape.Width( ) ) < s_chamberWidth && false == m_shape.HasCollision( m_xOffset + 1, m_yOffset, tower ) )
		++m_xOffset;
}

bool
Rock::TryFall( const RocksTower& tower )
{
	//if can fall down do it and return true, otherwise return false
	if( m_shape.HasCollision( m_xOffset, m_yOffset - 1, tower ) )
		return false;

	--m_yOffset;
	return true;
}

void
Rock::Rest( RocksTower& tower ) const
{
	if( false == m_shape.AddToTower( m_xOffset, m_yOffset, tower ) )
		throw std::logic_error( "Can't add to tower since there is collision!" );
}

size_t
Rock::Top( ) const
{
	return m_yOffset + m_shape.Height( );
}
