module;

#include <string>

export module not_enough_minerals:state;
import :types;
import :blocked_robots;

export namespace not_enough_minerals
{
	class Blueprint;

	struct State
	{
		MineralsQuantity m_gathered{ 0, 0, 0, 0 };
		MineralsQuantity m_builtRobots{ 1, 0, 0, 0 };//we start with 1 ore collecting robot
		MineralsQuantity m_robotsInConstruction{ 0, 0, 0, 0 };

		size_t m_remainingTime = 0;

		BlockedRobots m_blocked;

		State( size_t timeLimit );

		bool StepTime( );
		void ResetBlocked( );
		size_t Hash( ) const;
		bool CanBuildAnyRobotInFuture( const Blueprint& bp ) const;
		bool NoRobotsInProduction( ) const;
	};
}
