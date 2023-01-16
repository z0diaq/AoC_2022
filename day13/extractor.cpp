//dunno why below code does not work
//maybe some day I'll find out and make proper split
//note: toggle here and in extractor.ixx to expose problem

#if 0

import distress_signal;

using distress_signal::Extractor;
using distress_signal::Item;

#include <string>
#include <deque>
#include <iostream>
#include <stdexcept>

bool
Extractor::IsEof( ) const
{
	return m_it == m_data.end( );
}

Item
Extractor::ReadItem( )
{
	if( *m_it == ',' )
	{
		++m_it;

		if( IsEof( ) )
			throw std::logic_error( "No more data!" );
	}

	char c = *m_it;

	if( c == '[' )
	{
		++m_it;
		return Item( { .m_type = ItemType::ListOpen } );
	}
	else if( c == ']' )
	{
		++m_it;
		return Item( { .m_type = ItemType::ListClose } );
	}
	else if( std::isdigit( c ) )
	{
		unsigned int number = 0;
		while( std::isdigit( c ) )
		{
			number = 10 * number + c - '0';
			++m_it;
			c = *m_it;
		}
		return Item( {
			.m_type = ItemType::Number,
			.m_number = number } );
	}

	std::cerr << "Don't know what to do with [" << c << "] - fixme!" << std::endl;
	throw std::logic_error( "ReadItem failed to handle current type" );
}

Extractor::Extractor( const std::string& data ) :
	m_data( data )
{
	m_it = m_data.begin( );
}

std::deque<Item>
	Extractor::ExtractTokens( )
{
	std::deque<Item> tokens;
	while( false == this->IsEof( ) )
		tokens.push_back( this->ReadItem( ) );

	return tokens;
}
#endif
