module;

#include <string>
#include <deque>
#include <stdexcept>
#include <iostream>

export module distress_signal:extractor;

export import :item;

//dunno why below code extracted to source file does not work
//maybe some day I'll find out and make proper split
//note: toggle here and in extractor.cpp to expose problem

#if 1
export namespace distress_signal
{
	class Extractor
	{
		std::string                 m_data;
		std::string::const_iterator m_it;//parsing position

		[[nodiscard]] bool
		IsEof( ) const
		{
			return m_it == m_data.end( );
		}

		[[nodiscard]] Item
		ReadItem( )
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
	public:

		Extractor( const std::string& data ) :
			m_data( data )
		{
			m_it = m_data.begin( );
		}

		[[nodiscard]] std::deque<Item>
		ExtractTokens( )
		{
			std::deque<Item> tokens;
			while( false == this->IsEof( ) )
				tokens.push_back( this->ReadItem( ) );

			return tokens;
		}
	};
}
#else

export namespace distress_signal
{
	class Extractor
	{
		std::string                 m_data;
		std::string::const_iterator m_it;//parsing position

		[[nodiscard]] bool
		IsEof( ) const;

		[[nodiscard]] Item
		ReadItem( );
	public:

		Extractor( const std::string& data );

		[[nodiscard]] std::deque<Item>
		ExtractTokens( );
	};
}


#endif
