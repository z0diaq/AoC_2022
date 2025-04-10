export module grove_positioning_system:solver;

import :result;
import :types;

import <string>;
import <string_view>;
import <iostream>;
import <array>;
import <numeric>;
import <ranges>;

using namespace grove_positioning_system;
constexpr std::int64_t DECRYPTION_KEY = 811589153;

void
Result::ProcessOne( const std::string& data )
{
	m_values.push_back( Parse( data, m_values.size( ) ) );
}

std::string
Result::FinishPartOne( )
{
	return std::to_string( GetCoordinates( Mix( m_values ) ) );
}

void
Result::ProcessTwo( const std::string& data )
{
	ProcessOne( data );
	m_values.back( ).m_value *= DECRYPTION_KEY;
}

std::string
Result::FinishPartTwo( )
{
	auto copy = m_values;
	for( int i : std::ranges::iota_view{ 0, 10 } )
		copy = Mix( copy );
	return std::to_string( GetCoordinates( copy ) );
}

Value
Result::Parse( std::string_view _data, const size_t _rowNumber )
{
	return Value{ std::atoi( _data.data( ) ), _rowNumber };
}

Values
Result::Mix( const Values& _initialValues )
{
	const size_t size = _initialValues.size( );
	Values mixedValues = _initialValues;

	for( size_t originalIndex = 0; originalIndex < size; ++originalIndex )
	{
		auto it = std::find_if( mixedValues.begin( ), mixedValues.end( ),
			[originalIndex]( const Value& _value ) {
				return _value.m_position == originalIndex;
			} );

		if( it == mixedValues.end( ) )
			throw std::logic_error( "Item not found!" );

		int64_t currentPos = std::distance( mixedValues.begin( ), it );
		int64_t value = it->m_value;

		auto copy = *it;
		mixedValues.erase( it );

		int64_t move{ 0 };
		if( value )
			move = value % static_cast< int64_t >( size - 1 );

		int64_t newPos = ( currentPos + move ) % static_cast< int64_t >( size - 1 );
		if( newPos < 0 )
			newPos += ( size - 1 );
		if( newPos == 0 && move != 0 )
			newPos = size - 1;

		mixedValues.insert( mixedValues.begin( ) + newPos, copy );
	}

	return mixedValues;
}

int64_t
Result::GetCoordinates( const Values& _mixedValues )
{
	auto zeroIt = std::find_if( _mixedValues.begin( ), _mixedValues.end( ),
		[ ]( const Value& _value )
		{
			return _value.m_value == 0;
		} );

	if( zeroIt == _mixedValues.end( ) )
	{
		std::cerr << "Error: Value 0 not found in the mixed list" << std::endl;
		return 0;
	}

	size_t zeroPos = std::distance( _mixedValues.begin( ), zeroIt );
	size_t size = _mixedValues.size( );

	// Get values at 1000th, 2000th, and 3000th positions after 0
	std::array<int64_t, 3> coordinates;
	for( size_t i = 0; i < 3; ++i )
	{
		size_t pos = ( zeroPos + ( i + 1 ) * 1000 ) % size;
		coordinates[ i ] = _mixedValues[ pos ].m_value;
	}

	return std::accumulate( coordinates.begin( ), coordinates.end( ), static_cast< int64_t >( 0 ) );
}

