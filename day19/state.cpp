module;

#include <string>
#include <vector>

module not_enough_minerals:state;
import :blueprint;

using not_enough_minerals::State;
using not_enough_minerals::Blueprint;

State::State( size_t timeLimit ) :
	m_remainingTime( timeLimit )
{

}

bool
State::StepTime( )
{
	for( size_t robotType = 0; robotType != 4; ++robotType )
	{
		m_gathered[ robotType ] += m_builtRobots[ robotType ];

		m_builtRobots[ robotType ] += m_robotsInConstruction[ robotType ];
		m_robotsInConstruction[ robotType ] = 0;
	}

	return --m_remainingTime;
}

void
State::ResetBlocked( )
{
	m_blocked.Reset( );
}

size_t
State::Hash( ) const
{
	std::string value{
		static_cast< char >( m_remainingTime ),
		static_cast< char >( m_gathered[ Ore ] ),
		static_cast< char >( m_builtRobots[ Ore ] ),
		static_cast< char >( m_robotsInConstruction[ Ore ] ),
		static_cast< char >( m_blocked.IsBlocked( Ore ) ),

		static_cast< char >( m_gathered[ Clay ] ),
		static_cast< char >( m_builtRobots[ Clay ] ),
		static_cast< char >( m_robotsInConstruction[ Clay ] ),
		static_cast< char >( m_blocked.IsBlocked( Clay ) ),

		static_cast< char >( m_gathered[ Obsidian ] ),
		static_cast< char >( m_builtRobots[ Obsidian ] ),
		static_cast< char >( m_robotsInConstruction[ Obsidian ] ),
		static_cast< char >( m_blocked.IsBlocked( Obsidian ) ),

		static_cast< char >( m_gathered[ Geode ] ),
		static_cast< char >( m_builtRobots[ Geode ] ),
		static_cast< char >( m_robotsInConstruction[ Geode ] ),
		static_cast< char >( m_blocked.IsBlocked( Geode ) )
	};

	return std::hash<std::string>{}( value );
}

bool
State::CanBuildAnyRobotInFuture( const Blueprint& bp ) const
{
	MineralsQuantity mineralsInProduction{
		m_builtRobots[ Ore ] + m_robotsInConstruction[ Ore ] > 0,
		m_builtRobots[ Clay ] + m_robotsInConstruction[ Clay ] > 0,
		m_builtRobots[ Obsidian ] + m_robotsInConstruction[ Obsidian ] > 0,
		m_builtRobots[ Geode ] + m_robotsInConstruction[ Geode ] > 0 };

	std::vector<Type> buildableRobots = bp.RobotsFromMaterials( mineralsInProduction );

	//any not blocked robot ?
	for( size_t robot = 0; robot != buildableRobots.size( ); ++robot )
	{
		Type type = buildableRobots[ robot ];
		if( false == m_blocked.IsBlocked( type ) )
			return true;
	}

	return false;
}

bool
State::NoRobotsInProduction( ) const
{
	return
		0 == m_robotsInConstruction[ Ore ] &&
		0 == m_robotsInConstruction[ Clay ] &&
		0 == m_robotsInConstruction[ Obsidian ] &&
		0 == m_robotsInConstruction[ Geode ];
}
