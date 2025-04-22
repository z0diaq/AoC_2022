export module monkey_math:solver;

import :result;
import :types;

import <string>;
import <optional>;
import <stdexcept>;
import <iostream>;

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
	return std::to_string( 0 );
}

void
Result::ProcessTwo( const std::string& data )
{
}

std::string
Result::FinishPartTwo( )
{
	return std::to_string( 0 );
}
