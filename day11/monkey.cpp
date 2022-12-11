import monkey_in_the_middle;

#include <iostream>
#include <string>
#include <stdexcept>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

using namespace monkey_in_the_middle;

unsigned int Monkey::m_commonMultiple = 1;

void
Monkey::Init( )
{
	m_commonMultiple = 1;
}

void
Monkey::ParseLine( const std::string& line )
{
	if( line.empty( ) )
		return;

	if( line.substr( 0, 17 ) == "  Starting items:" )
	{
		std::vector<std::string> items;
		boost::split( items, line.substr( 18 ), boost::is_any_of( ", " ), boost::algorithm::token_compress_on );
		for( const auto& item : items )
			m_items.push_back( boost::lexical_cast< unsigned int >( item ) );

		m_performedInspects = 0;
	}
	else if( line.substr( 0, 12 ) == "  Operation:" )
	{
		std::vector<std::string> operands;
		boost::split( operands, line.substr( 19 ), boost::is_any_of( " " ) );

		m_operationType = OperationType::Multiplication;
		if( operands[ 1 ] == "+" )
			m_operationType = OperationType::Addition;

		if( operands[ 2 ] == "old" && m_operationType == OperationType::Multiplication )
			m_operationType = OperationType::Square;
		else
			m_operationOperand = boost::lexical_cast< unsigned int >( operands[ 2 ] );
	}
	else if( line.substr( 0, 7 ) == "  Test:" )
	{
		auto part = line.substr( 21 );
		m_testValue = boost::lexical_cast< unsigned int >( part );
		m_commonMultiple *= m_testValue;
	}
	else if( line.substr( 0, 12 ) == "    If true:" )
	{
		m_recipientIfTrue = boost::lexical_cast< unsigned int >( line.substr( 29 ) );
	}
	else if( line.substr( 0, 13 ) == "    If false:" )
	{
		m_recipientIfFalse = boost::lexical_cast< unsigned int >( line.substr( 30 ) );
	}
	else
	{
		std::cout << "Unrecognized line:" << line << std::endl;
		throw std::logic_error( "Unrecognized line detected!" );
	}
}

void
Monkey::ShowInfo( ) const
{
	std::cout << "\tItems:";
		for( auto item : m_items )
			std::cout << " " << item;
	std::cout << std::endl;

	std::cout << "\tOperation new = old ";
	switch( m_operationType )
	{
	case OperationType::Addition:
		std::cout << "+ " << m_operationOperand;
		break;
	case OperationType::Multiplication:
		std::cout << "* " << m_operationOperand;
		break;
	case OperationType::Square:
		std::cout << "* old";
		break;
	}
	std::cout << std::endl;

	std::cout << "\tTest: divisible by " << m_testValue << std::endl;
	std::cout << "\t  If true: throw to monkey " << m_recipientIfTrue << std::endl;
	std::cout << "\t  If false: throw to monkey " << m_recipientIfFalse << std::endl;
}
