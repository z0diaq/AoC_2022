module;

#include <iostream>
#include <vector>
#include <algorithm>

export module calorie_counting;

export import :data;


export namespace calorie_counting
{
	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual bool ProcessGeneral( const AoC::DataPtr& data ) override;
		virtual bool ProcessOne( const AoC::DataPtr& data ) override;
		virtual bool ProcessTwo( const AoC::DataPtr& data ) override;
		virtual uint64_t Finish( ) const override;
		virtual void Teardown( ) override;

	private:
		std::vector<uint32_t> m_caloriesSumsPerElf;

		//part one section
		virtual uint64_t FinishPartOne( ) const;

		//part two section
		virtual uint64_t FinishPartTwo( ) const;
	};
}

using namespace calorie_counting;

Result::Result( )
{
}

void
Result::Init( )
{
	m_data.reset( new calorie_counting::Data( ) );
	m_haveDedicatedProcessing = false;
	m_caloriesSumsPerElf.resize( 1 );
}

void
Result::Teardown( )
{
	m_data.reset( );
	m_caloriesSumsPerElf.clear( );
}

bool
Result::ProcessGeneral( const AoC::DataPtr& data )
{
	auto dataDerived = static_cast< calorie_counting::Data* >( data.get( ) );
	if( dataDerived->m_calories )
		m_caloriesSumsPerElf.back( ) += dataDerived->m_calories;
	else
		m_caloriesSumsPerElf.push_back( 0u );

	return true;//drop data, we used all
}

bool
Result::ProcessOne( const AoC::DataPtr& data )
{
	return true;//drop data, we used all
}

bool
Result::ProcessTwo( const AoC::DataPtr& data )
{
	return true;//drop data, we used all
}

uint64_t
Result::Finish( ) const
{
	const uint64_t result = IsPartOne( ) ? FinishPartOne( ) : FinishPartTwo( );
	std::cout
		<< "result = "
		<< result
		<< std::endl;

	return result;
}

uint64_t
Result::FinishPartOne( ) const
{
	auto dataCopy = m_caloriesSumsPerElf;
	std::sort( dataCopy.begin( ), dataCopy.end( ) );
	return dataCopy.back( );
}

uint64_t
Result::FinishPartTwo( ) const
{
	auto dataCopy = m_caloriesSumsPerElf;
	std::sort( dataCopy.begin( ), dataCopy.end( ) );
	size_t count = dataCopy.size( );

	return dataCopy[ count - 1 ] + dataCopy[ count - 2 ] + dataCopy[ count - 3 ];
}