export module monkey_math:solver;

import :result;
import :types;

import <string>;
import <optional>;
import <stdexcept>;
import <iostream>;

import <boost/algorithm/string/split.hpp>;
import <boost/algorithm/string/classification.hpp>;

using namespace monkey_math;

std::optional<std::pair<std::string, std::string> >
Result::ProcessLine( const std::string& _line )
{
	if( _line.length( ) < 7 )
		return std::nullopt;
	size_t pos = _line.find( ": " );
	if( pos == std::string::npos )
	{
		std::cerr << "Invalid line detected: " << _line << std::endl;
		throw std::runtime_error( "Line is not a valid operation" );
	}

	return std::make_pair( _line.substr( 0, pos ), _line.substr( pos + 2 ));
}

void
Result::ProcessOne( const std::string& data )
{
	auto splitResult = ProcessLine( data );
	if( splitResult.has_value( ) )
		m_monkeys[ splitResult->first ] = splitResult->second;
}

std::string
Result::FinishPartOne( )
{
	return std::to_string( Evaluate( m_monkeys, "root" ) );
}

void
Result::ProcessTwo( const std::string& data )
{
	ProcessOne( data );
}

std::string
Result::FinishPartTwo( )
{
	std::int64_t low = 0, high = std::numeric_limits<std::int64_t>::max();
	MonkeyMath monkeys = m_monkeys;

	const auto it = monkeys.find( "root" );
	if( it == monkeys.end( ) )
	{
		std::cout << "Monkey [root] is not in the map!" << std::endl;
		throw std::logic_error( "No root!" );
	}
	const std::string& operation = it->second;

	if( operation.empty( ) )
	{
		std::cerr << "Monkey [root] has empty operation!" << std::endl;
		throw std::logic_error( "Empty operation line detected!" );
	}

	std::vector<std::string> parts;
	boost::split( parts, operation, boost::is_any_of( " " ) );

	if( parts.size( ) != 3 )
	{
		std::cerr << "Operation [" << operation << "] expected to have 3 parts but have " << parts.size( ) << std::endl;
		throw std::logic_error( "Operation has invalid number of parts!" );
	}
	if( parts[ 1 ].length( ) != 1 )
	{
		std::cerr << "Operator [" << parts[ 1 ] << "] expected to be of 1-length but is " << parts[ 1 ].length( ) << std::endl;
		throw std::logic_error( "Invalid operator!" );
	}

	const std::string left = parts[ 0 ];
	const std::string right = parts[ 2 ];

	bool increasing{ false };
	{
		MonkeyMath temp = m_monkeys;

		temp[ "humn" ] = "1";
		auto base_lhs = Evaluate( temp, left );
		auto base_rhs = Evaluate( temp, right );
		auto base_diff = base_lhs - base_rhs;

		temp[ "humn" ] = "2";
		auto next_diff = Evaluate( temp, left ) - Evaluate( temp, right );

		increasing = next_diff > base_diff;
	}

	while( low <= high )
	{
		std::int64_t mid = ( low + high ) / 2;
		monkeys[ "humn" ] = std::to_string( mid );
		auto lhs = Evaluate( monkeys, left );
		auto rhs = Evaluate( monkeys, right );

		if( lhs == rhs )
			return std::to_string( mid );
		else if( lhs < rhs )
			low = mid + 1;
		else
			high = mid - 1;
	}
	return std::to_string( 0 );
}

std::int64_t
Result::Evaluate( const MonkeyMath& _monkeys, const std::string& _name )
{
	const auto it = _monkeys.find( _name );
	if( it == _monkeys.end( ) )
	{
		std::cout << "Monkey [" << _name << "] is not in the map!" << std::endl;
		throw std::logic_error( "Unknown monkey!" );
	}
	const std::string& operation = it->second;

	if( operation.empty( ) )
	{
		std::cerr << "Monkey [" << _name << "] has empty operation!" << std::endl;
		throw std::logic_error( "Empty operation line detected!" );
	}

	if( std::isdigit( operation.front( ) ) || operation.front( ) == '-' )
		return std::atoll( operation.c_str( ) );

	std::vector<std::string> parts;
	boost::split( parts, operation, boost::is_any_of( " " ) );

	if( parts.size( ) != 3  )
	{
		std::cerr << "Operation [" << operation << "] expected to have 3 parts but have " << parts.size( ) << std::endl;
		throw std::logic_error( "Operation has invalid number of parts!" );
	}
	if( parts[ 1 ].length( ) != 1 )
	{
		std::cerr << "Operator [" << parts[ 1 ] << "] expected to be of 1-length but is " << parts[ 1 ].length( ) << std::endl;
		throw std::logic_error( "Invalid operator!" );
	}

	std::int64_t lhs = Evaluate( _monkeys, parts[ 0 ] ),
	             rhs = Evaluate( _monkeys, parts[ 2 ] );

	switch( parts[ 1 ][ 0 ] )
	{
	case '+':
		return lhs + rhs;
	case '-':
		return lhs - rhs;
	case '*':
		return lhs * rhs;
	case '/':
		return lhs / rhs;
	default:
		std::cerr << "Operator [" << parts[ 1 ] << "] is not handled!" << std::endl;
		throw std::logic_error( "Unhnandled operator" );
	}
}
