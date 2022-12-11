import monkey_in_the_middle;

#include <iostream>
#include <string>

using namespace monkey_in_the_middle;

bool
Monkey::InspectNextItem( uint64_t& item, size_t& recipient, bool isPartOne )
{
	if( m_items.empty( ) )
	{
		std::cout << "  Monkey has not items to inspect" << std::endl;
		return false;
	}

	item = m_items.front( );
	m_items.pop_front( );

	++m_performedInspects;

	std::cout << "  Monkey inspects an item with worry level of " << item << std::endl;
	PerformOperation( item );
	std::cout << "    Worry level changes to " << item << std::endl;
	item %= m_commonMultiple;
	if( isPartOne )
		item /= 3;
	std::cout << "    Monkey gets bored with item. Worry level is divided by 3 to " << item << std::endl;
	bool isDivisible = ( item % m_testValue == 0 );
	std::cout << "    Current worry level is " << ( isDivisible ? "" : "not " ) << "divisible by " << m_testValue << std::endl;
	recipient = ( isDivisible ? m_recipientIfTrue : m_recipientIfFalse );
	std::cout << "    Item with worry level " << item << " is thrown to monkey " << recipient << std::endl;

	return true;
}

void
Monkey::PerformOperation( uint64_t& value )
{
	switch( m_operationType )
	{
	case OperationType::Addition:
		value += m_operationOperand;
		break;
	case OperationType::Multiplication:
		value *= m_operationOperand;
		break;
	case OperationType::Square:
		value *= value;
		break;
	}
}

void
Monkey::GiveItem( uint64_t item )
{
	m_items.push_back( item );
}
