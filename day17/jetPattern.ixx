module;

#include <string>

export module pyroclastic_flow:jet_pattern;

export namespace pyroclastic_flow
{
	class Rock;
	class RocksTower;

	struct JetPattern
	{
		std::string m_pattern;
		size_t m_currentIndex = 0;

		void Apply( Rock& rock, const RocksTower& tower );
	};
}
