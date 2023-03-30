import not_enough_minerals;

#include <iostream>

#include <set>
#include <deque>

using namespace not_enough_minerals;

size_t
Result::MostGeodesCollected( const Blueprint& bp, size_t timeLimit ) const
{
	size_t result = 0;
	State state( timeLimit );

	std::deque<State> stateList{ state };

	std::set<size_t> alreadyProcessed;//no need to store full data, just go for hashes to identify already processed states

	auto AddIfNotProcessed = [&stateList, &alreadyProcessed]( const State& state ) -> void
	{
		size_t hash = state.Hash( );

		if( alreadyProcessed.count( hash ) )
			return;

		stateList.push_back( state );
		alreadyProcessed.insert( hash );
	};

	while( false == stateList.empty( ) )
	{
		state = stateList.front( );
		stateList.pop_front( );

		//how many geodes we can produce at most with this state
		size_t maxPossibleGeodes = state.m_gathered[ Geode ];
		size_t newGeodeRobots = 0;
		for( size_t timeRemaining = state.m_remainingTime; timeRemaining > 0; --timeRemaining )
			maxPossibleGeodes += state.m_builtRobots[ Geode ] + newGeodeRobots++;

		if( maxPossibleGeodes < result )
			continue;

		bool blockedAnyRobot = this->BlockIfEnoughRobots( state, bp );

		if( state.NoRobotsInProduction( ) )
		{
			//how many different robots we can build now ?
			auto buildableRobots = bp.BuildableRobots( state );

			for( int type : buildableRobots )
			{
				if( ShouldBuild( state, static_cast< Type >( type ), bp ) )
				{
					AddIfNotProcessed(
						bp.Produce(
						state,
						static_cast< Type >( type ) ) );
					state.m_blocked.Block( static_cast< Type >( type ) );
					blockedAnyRobot = true;
				}
			}
		}

		if( state.StepTime( ) )
		{
			if( false == blockedAnyRobot || state.CanBuildAnyRobotInFuture( bp ) )
				AddIfNotProcessed( state );
		}
		else
		{
			const size_t goedesGathered = state.m_gathered[ Geode ];
			result = std::max( result, goedesGathered );
		}
	}

	std::cout << "Geodes collected:" << result << std::endl;

	return result;
}
