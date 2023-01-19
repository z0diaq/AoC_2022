module;

#include <string>
#include <vector>

export module pyroclastic_flow:rock_shape;

export namespace pyroclastic_flow
{
	class RocksTower;

	class RockShape
	{
		std::vector<std::string> m_data;
		size_t m_width = 0;

	public:
		RockShape( const std::vector<std::string>& data );

		[[nodiscard]] size_t Width( ) const;
		[[nodiscard]] size_t Height( ) const;

		[[nodiscard]] bool HasCollision( const size_t xOffset, const size_t yOffset, const RocksTower& tower ) const;
		[[nodiscard]] bool AddToTower( const size_t xOffset, const size_t yOffset, RocksTower& tower ) const;
	};
}
