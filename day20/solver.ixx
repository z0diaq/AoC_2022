export module grove_positioning_system:solver;

import :result;
import :types;

import <string>;
import <string_view>;

using namespace grove_positioning_system;

void
Result::ProcessOne( const std::string& data )
{
	m_values.push_back( Parse( data, m_values.size( ) ) );
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

Value
Result::Parse( std::string_view _data, const size_t _rowNumber )
{
	return Value{ std::atoi( _data.data( ) ), _rowNumber };
}

Values
Result::Mix( const Values& _initialValues )
{
	// TODO: perform mixing

	return _initialValues;
}

