module;

#include <string>
#include <vector>
#include <deque>
#include <stdexcept>

export module pyroclastic_flow:rock;

export namespace pyroclastic_flow
{
	class RocksTower;
	class RockShape;

	class Rock
	{
		const RockShape& m_shape;
		size_t m_xOffset;
		size_t m_yOffset;

	public:
		Rock( const RockShape& shape, const size_t yOffset );

		void TryMoveLeft( const RocksTower& tower );
		void TryMoveRight( const RocksTower& tower );

		[[nodiscard]] size_t Top( ) const;

		[[nodiscard]] bool TryFall( const RocksTower& tower );
		void Rest( RocksTower& tower ) const;
	};
}
