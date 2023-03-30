module;

#include <array>

export module not_enough_minerals:robot_cost;
import :types;

export namespace not_enough_minerals
{


	// FIXME: too many static_cast - find better way


	class RobotCost
	{
		MineralsQuantity m_cost;
	public:
		RobotCost( size_t ore, size_t clay, size_t obsidian );

		bool Consume( MineralsQuantity& gathered ) const;
		bool EnoughMinerals( const MineralsQuantity& gathered ) const;
		size_t Cost( int type ) const;
		bool HaveRequiredMinerals( const MineralsQuantity& providedMinerals ) const;
	};
}
