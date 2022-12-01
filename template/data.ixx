module;

#include <string>

export module calorie_counting:data;

export import AoC;

export namespace calorie_counting
{
	struct Data : public AoC::Data
	{
		virtual void Process( const std::string& line ) override;
		virtual void Reset( ) override;
	};
}

using namespace calorie_counting;

void
Data::Process( const std::string& line )
{
}

void
Data::Reset( )
{
}
