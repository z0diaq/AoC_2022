module;

#include <array>
#include <vector>

export module not_enough_minerals:blueprint;
import :types;
import :state;
import :robot_cost;

export namespace not_enough_minerals
{
	class Blueprint
	{
		std::array<RobotCost, 4> m_robotsCosts;
		MineralsQuantity m_maxCost{ 0, 0, 0, 0 };//we can produce at most 1 new robot so prepare in advance maximum cost of each mineral we should be producing

	public:
		Blueprint( const RobotCost& oreRobot, const RobotCost& clayRobot, const RobotCost& obsidianRobot, const RobotCost& geodeRobot );

		// produce robot if we can afford it
		State Produce( const State& state, Type type ) const;
		std::vector<Type> BuildableRobots( const State& state ) const;
		bool WorthBuilding( Type type, const size_t builtRobots ) const;
		std::vector<Type> RobotsFromMaterials( const MineralsQuantity& mineralsInProduction ) const;
	};
}
