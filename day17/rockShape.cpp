module;

#include <vector>
#include <string>

module pyroclastic_flow:rock_shape;
import :rocks_tower;

using namespace pyroclastic_flow;

RockShape::RockShape( const std::vector<std::string>& data ) :
	m_data( data )
{
	for( const auto& line : data )
		m_width = std::max( m_width, line.length( ) );

	//simplify HasCollision processing
	std::reverse( m_data.begin( ), m_data.end( ) );
}

size_t
RockShape::Width( ) const
{
	return m_width;
}

size_t
RockShape::Height( ) const
{
	return m_data.size( );
}

bool
RockShape::HasCollision( const size_t xOffset, const size_t yOffset, const RocksTower& tower ) const
{
	for( size_t rowNo = 0; rowNo != m_data.size( ); ++rowNo )
	{
		const std::string& line = m_data[ rowNo ];
		for( size_t columnNo = 0; columnNo != line.length( ); ++columnNo )
		{
			if( line[ columnNo ] != '#' )
				continue;
			if( tower.IsUsed( xOffset + columnNo, yOffset + rowNo ) )
				return true;
		}
	}
	return false;
}

bool
RockShape::AddToTower( const size_t xOffset, const size_t yOffset, RocksTower& tower ) const
{
	for( size_t rowNo = 0; rowNo != m_data.size( ); ++rowNo )
	{
		const std::string& line = m_data[ rowNo ];
		for( size_t columnNo = 0; columnNo != line.length( ); ++columnNo )
		{
			if( line[ columnNo ] != '#' )
				continue;
			if( false == tower.RestRock( xOffset + columnNo, yOffset + rowNo ) )
				return false;
		}
	}
	return true;

}
