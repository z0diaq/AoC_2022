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
	auto[m_columnsContinuations, m_rowsContinuations] = AnalyzeMap( m_map );

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
		if( scanLine.length( ) != mapWidth )
		{
			std::cerr << "First row has length of " << mapWidth << " while current has length of " << scanLine.length( ) << std::endl;
			std::cerr << "Line: [" << row << "]" << std::endl;
			throw std::logic_error( "Map is not consistent!" );
		}

		for( int column{ 0 }; column != maxColumn; ++column )
		{
			if( scanLine[ column ] != ' ' )
			{
				columnsContinuations[ column ].first = std::min( columnsContinuations[ column ].first, row );
				columnsContinuations[ column ].second = std::max( columnsContinuations[ column ].second, row );

				rowsContinuations[ row ].first = std::min( rowsContinuations[ row ].first, column );
				rowsContinuations[ row ].second = std::max( rowsContinuations[ row ].second, column );
			}
		}
	}
	return { columnsContinuations, rowsContinuations };
}
