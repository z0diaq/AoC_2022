import pyroclastic_flow;

#include <string>

using namespace pyroclastic_flow;

Result::Result()
{
	PrepareShapes( );
}

void
Result::Init()
{
	m_tower = RocksTower( );
	m_jetPattern = JetPattern( );

	m_skippedHeight = 0;
}

void
Result::PrepareShapes( )
{
	m_shapes.push_back( RockShape{ { "####" } } );

	m_shapes.push_back( RockShape{ { " # ",
									 "###",
									 " # " } } );

	m_shapes.push_back( RockShape{ { "  #",
									 "  #",
									 "###" } } );

	m_shapes.push_back( RockShape{ { "#",
									 "#",
									 "#",
									 "#" } } );

	m_shapes.push_back( RockShape{ { "##",
									 "##" } } );
}

void
Result::Teardown()
{
	m_seenHashes.clear( );
}

void
Result::DropRocks( size_t count )
{
	size_t hash = 0;
	const size_t hashRange = m_jetPattern.m_pattern.length( );
	bool foundHash = false;
	for( size_t rockNo = 0; rockNo != count; ++rockNo )
	{
		ProcessRock( CreateRock( rockNo ) );

		if( false == foundHash && m_tower.TryBuildHash( hash, hashRange ) )
		{
			if( m_seenHashes.count( hash ) )
			{
				const auto& info = m_seenHashes.at( hash );
				const size_t rocksDiff = rockNo - info.first;
				const size_t heightDiff = m_tower.Height( ) - info.second;

				const size_t repeats = ( count - rockNo ) / rocksDiff;
				rockNo += repeats * rocksDiff;
				m_skippedHeight = repeats * heightDiff;
				foundHash = true;
			}
			else
				m_seenHashes[ hash ] = { rockNo, m_tower.Height( ) };
		}
	}
}

size_t
Result::TowerHeight( ) const
{
	return m_skippedHeight + m_tower.Height( );
}

Rock
Result::CreateRock( const size_t rockNo ) const
{
	const size_t yOffset = m_tower.Height( ) + 4ull;
	const RockShape& currentShape = m_shapes[ rockNo % m_shapes.size( ) ];

	return Rock( currentShape, yOffset );
}
