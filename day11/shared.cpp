import monkey_in_the_middle;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>

using namespace monkey_in_the_middle;

std::string
Result::FinishCommon( unsigned int iterations )
{
	for( const auto& it : m_monkeys )
	{
		std::cout << "Monkey " << it.first << std::endl;
		it.second.ShowInfo( );
	}

	std::cout << "common multiple:" << Monkey::m_commonMultiple << std::endl;

	uint64_t item{ 0 };
	size_t recipient{ 0 };
	for( unsigned int round = 0; round != iterations; ++round )
	{
		for( auto& it : m_monkeys )
		{
			std::cout << "Monkey " << it.first << std::endl;
			while( it.second.InspectNextItem( item, recipient, IsPartOne( ) ) )
			{
				m_monkeys[ recipient ].GiveItem( item );
			}
		}
	}

	std::vector<uint64_t> inspectsPerMonkey( m_monkeys.size( ), 0 );
	for( unsigned int monkeyNo = 0; monkeyNo != m_monkeys.size( ); ++monkeyNo )
		inspectsPerMonkey[ monkeyNo ] = m_monkeys[ monkeyNo ].PerformedInspects( );

	std::sort( inspectsPerMonkey.begin( ), inspectsPerMonkey.end( ) );
	std::cout << *( inspectsPerMonkey.end( ) - 1 ) << " " << *( inspectsPerMonkey.end( ) - 2 ) << std::endl;
	return std::to_string( *( inspectsPerMonkey.end( ) - 1 ) * *( inspectsPerMonkey.end( ) - 2 ) );
}

void
Result::Init()
{
	m_currentMonkey = nullptr;
	Monkey::Init( );
}

void
Result::Teardown()
{
	m_monkeys.clear( );
}
