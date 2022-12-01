module;

#include <string>
#include <boost/lexical_cast.hpp>

export module calorie_counting:data;

export import AoC;

export namespace calorie_counting
{
	struct Data : public AoC::Data
	{
		uint32_t m_calories;

		virtual void Process( const std::string& line ) override;
		virtual void Reset( ) override;
	};
}

using namespace calorie_counting;

void
Data::Process( const std::string& line )
{
	if( false == line.empty( ) )
		m_calories = boost::lexical_cast< uint32_t >( line );
}

void
Data::Reset( )
{
	m_calories = 0;
}
