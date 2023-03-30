module;

#include <array>

export module not_enough_minerals:types;

export namespace not_enough_minerals
{
	enum Type : int
	{
		Ore,
		Clay,
		Obsidian,
		Geode
	};

	typedef std::array<size_t, 4> MineralsQuantity;
}
