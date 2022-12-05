module;

#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/lexical_cast.hpp>

export module calorie_counting;

import AoC;

export namespace calorie_counting
{
	class Result : public AoC::Result
	{

	protected:
		virtual void Init( ) override;

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown( ) override;

	private:
		std::vector<uint64_t> m_caloriesSumsPerElf;

		void ProcessGeneral( const std::string& line );
	};
}

using namespace calorie_counting;

void
Result::Init( )
{
	m_caloriesSumsPerElf.resize( 1 );
}

void
Result::Teardown( )
{
	m_caloriesSumsPerElf.clear( );
}

void
Result::ProcessOne( const std::string& data )
{
	ProcessGeneral( data );
}

void
Result::ProcessTwo( const std::string& data )
{
	ProcessGeneral( data );
}

void
Result::ProcessGeneral( const std::string& data )
{
	if( false == data.empty( ) )
		m_caloriesSumsPerElf.back( ) += boost::lexical_cast< uint64_t >( data );
	else
		m_caloriesSumsPerElf.push_back( 0u );
}

std::string
Result::FinishPartOne( )
{
	std::sort( m_caloriesSumsPerElf.begin( ), m_caloriesSumsPerElf.end( ) );
	return std::to_string( m_caloriesSumsPerElf.back( ) );
}

std::string
Result::FinishPartTwo( )
{
	std::sort( m_caloriesSumsPerElf.begin( ), m_caloriesSumsPerElf.end( ) );
	size_t count = m_caloriesSumsPerElf.size( );

	return std::to_string( m_caloriesSumsPerElf[ count - 1 ] + m_caloriesSumsPerElf[ count - 2 ] + m_caloriesSumsPerElf[ count - 3 ] );
}