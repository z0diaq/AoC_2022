export module monkey_map:solver;

import :result;
import :types;

import <string>;
import <stdexcept>;
import <iostream>;

using namespace monkey_map;

void
Result::ProcessOne( const std::string& data )
{
	if( data.empty( ) )
		return;
	switch( data.front( ) )
	{
	case '.':
	case ' ':
	case '#':
		m_map.push_back( data );
		break;
	default:
		if( false == m_pathToFollow.empty( ) )
			throw std::logic_error( "Path already set - can't do this twice!" );
		m_pathToFollow = data;
	}
}


std::string
Result::FinishPartOne( )
{
	auto [m_columnsContinuations, m_rowsContinuations] = AnalyzeMap( m_map );
	Position position( m_rowsContinuations[ 0 ].first, 0 ); // we can use the continuations' data to get initial position



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

std::tuple<Continuations, Continuations>
Result::AnalyzeMap( const BoardMap& _map )
{
	if( _map.empty( ) || _map.front( ).empty( ) )
		throw std::logic_error( "Map is empty!" );

	// assumption - each row has same length
	const size_t mapWidth{ _map.front( ).length( ) };
	const size_t mapHeight{ _map.size( ) };
	const int maxColumn = static_cast< int >( mapWidth );
	const int maxRow = static_cast< int >( mapHeight );
	Continuations rowsContinuations = Continuations( _map.size( ), { maxColumn, 0 } );
	Continuations columnsContinuations = Continuations( mapWidth, { maxRow, 0 } );
	for( int row{ 0 }; row != maxRow; ++row )
	{
		const std::string scanLine{ _map.at( row ) };
		while( columnsContinuations.size( ) < scanLine.length( ) )
			columnsContinuations.push_back( { maxRow, 0 } );

		for( size_t column{ 0 }; column != scanLine.length( ); ++column )
		{
			switch( scanLine[ column ] )
			{
			case '.':
			case '#':
				columnsContinuations[ column ].first = std::min( columnsContinuations[ column ].first, row );
				columnsContinuations[ column ].second = std::max( columnsContinuations[ column ].second, row );

				rowsContinuations[ row ].first = std::min( rowsContinuations[ row ].first, (int)column );
				rowsContinuations[ row ].second = std::max( rowsContinuations[ row ].second, (int)column );
				break;
			case ' ':
				continue;
			default:
				std::cerr << "Scanline [" << scanLine << "]" << std::endl;
				throw std::logic_error( "Data has invalid character(s)!" );
			}
		}
	}
	return { columnsContinuations, rowsContinuations };
}

Actions
Result::GetActions( const std::string& _pathToFollow )
{
	Actions result;

	int number = 0;
	bool isNumber{ false };
	for( char c : _pathToFollow )
	{
		switch( c )
		{
		case 'L':
		case 'R':
			if( isNumber )
				result.push_back( number );
			result.push_back( Action( c == 'L' ? Turn::Left : Turn::Right ) );
			isNumber = false;
			number = 0;
			break;
		default: // number
			isNumber = true;
			number = 10 * number + ( c - '0' );
			break;
		}
	}

	// handle case when number is last iteam
	if( isNumber )
		result.push_back( number );

	return result;
}
