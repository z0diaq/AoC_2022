module;

#include <string>
#include <deque>

export module pyroclastic_flow:rocks_tower;

export namespace pyroclastic_flow
{
	constexpr size_t s_chamberWidth = 7;

	class Rock;

	struct RocksTower
	{
		//todo: convert to bitset after whole algorithm is working
		std::deque<std::string> m_scan{ std::string( s_chamberWidth, '#' ) };
		size_t m_currentHeight = 0;

	public:

		void PrepareForNewRock( const Rock& rock );
		size_t Height( ) const;
		[[nodiscard]] bool IsUsed( size_t xOffset, size_t yOffset ) const;
		[[nodiscard]] bool RestRock( size_t xOffset, size_t yOffset );
		[[nodiscard]] bool TryBuildHash( size_t& hash, const size_t range );
	};
}
