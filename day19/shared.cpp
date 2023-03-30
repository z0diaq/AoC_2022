import not_enough_minerals;

#include <iostream>
#include <string>
#include <stdexcept>

#include <regex>

using namespace not_enough_minerals;

void
Result::Init( )
{
	m_lineRegex = "Blueprint (\\d+): Each ore robot costs (\\d+) ore. Each clay robot costs (\\d+) ore. Each obsidian robot costs (\\d+) ore and (\\d+) clay. Each geode robot costs (\\d+) ore and (\\d+) obsidian.";
	//             0            1                            2                                 3                                     4              5                                   6              7
}

void
Result::Teardown()
{
	m_blueprints.clear( );
}

void
Result::Process( const std::string& data )
{
	std::smatch lineParts;
	if( std::regex_match( data, lineParts, m_lineRegex ) )
	{
		m_blueprints.push_back(
			Blueprint(
			RobotCost( std::stoull( lineParts[ 2 ].str( ) ), 0, 0 ),
			RobotCost( std::stoull( lineParts[ 3 ].str( ) ), 0, 0 ),
			RobotCost( std::stoull( lineParts[ 4 ].str( ) ), std::stoull( lineParts[ 5 ].str( ) ), 0 ),
			RobotCost( std::stoull( lineParts[ 6 ].str( ) ), 0, std::stoull( lineParts[ 7 ].str( ) ) )
		)
		);
	}
	else
	{
		std::cerr << "ERROR: line [" << data << "] not matched by regex - please check!";
		throw std::logic_error( "Unmatched line!" );
	}
}

bool
Result::ShouldBuild( const State& state, Type type, const Blueprint& bp ) const
{
	return false == state.m_blocked.IsBlocked( type ) &&
		bp.WorthBuilding( type, state.m_builtRobots[ type ] );
}

bool
Result::BlockIfEnoughRobots( State& state, const Blueprint& bp ) const
{
	bool changed = false;
	for( int type = 0; type != 4; ++type )
	{
		if( false == state.m_blocked.IsBlocked( static_cast< Type >( type ) ) &&
			false == bp.WorthBuilding( static_cast< Type >( type ), state.m_builtRobots[ type ] ) )
		{
			state.m_blocked.Block( static_cast< Type >( type ) );
			changed = true;
		}
	}

	return changed;
}
