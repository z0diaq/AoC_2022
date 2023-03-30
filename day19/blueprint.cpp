module;

#include <vector>
#include <stdexcept>

module not_enough_minerals:blueprint;
import :robot_cost;
import :state;
import :types;

using not_enough_minerals::State;
using not_enough_minerals::Blueprint;
using not_enough_minerals::RobotCost;
using not_enough_minerals::Type;
using not_enough_minerals::MineralsQuantity;

Blueprint::Blueprint( const RobotCost& oreRobot, const RobotCost& clayRobot, const RobotCost& obsidianRobot, const RobotCost& geodeRobot ) :
	m_robotsCosts{ oreRobot, clayRobot, obsidianRobot, geodeRobot }
{
	for( int robotType = 0; robotType < 4; ++robotType )
	{
		for( int mineralType = 0; mineralType < 4; ++mineralType )
			m_maxCost[ mineralType ] = std::max( m_maxCost[ mineralType ], m_robotsCosts[ robotType ].Cost( mineralType ) );
	}
}

State
Blueprint::Produce( const State& state, Type type ) const
{
	const RobotCost& cost = m_robotsCosts[ type ];
	State result = state;
	if( false == cost.Consume( result.m_gathered ) )
		throw std::logic_error( "Tried to build robot but don't have minerals" );

	result.ResetBlocked( );
	++result.m_robotsInConstruction[ type ];
	return result;
}

std::vector<Type>
Blueprint::BuildableRobots( const State& state ) const
{
	std::vector<Type> result;
	for( int type = 0; type != 4; ++type )
		if( m_robotsCosts[ type ].EnoughMinerals( state.m_gathered ) )
			result.push_back( static_cast< Type >( type ) );

	return result;
}

bool
Blueprint::WorthBuilding( Type type, const size_t builtRobots ) const
{
	return builtRobots < m_maxCost[ type ] || type == Geode;
}

std::vector<Type>
Blueprint::RobotsFromMaterials( const MineralsQuantity& mineralsInProduction ) const
{
	std::vector<Type> result;
	for( int type = 0; type != 4; ++type )
	{
		if( m_robotsCosts[ type ].HaveRequiredMinerals( mineralsInProduction ) )
			result.push_back( static_cast< Type >( type ) );
	}

	return result;
}
