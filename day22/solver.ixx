export module monkey_map:solver;

import :result;
import :types;

import <string>;
import <stdexcept>;
import <iostream>;
import <variant>;

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

namespace
{
	int DirectionValue( Direction _direction )
	{
		switch( _direction )
		{
		case Direction::Right:
			return 0;
		case Direction::Down:
			return 1;
		case Direction::Left:
			return 2;
		case Direction::Up:
			return 3;
		}
		throw std::logic_error( "Invalid direction value!" );
	}

	constexpr Direction MakeTurn( Turn _turn, Direction _currentDirection )
	{
		if( _turn == Turn::Right )
		{
			switch( _currentDirection )
			{
			case Direction::Right:
				return Direction::Down;
			case Direction::Down:
				return Direction::Left;
			case Direction::Left:
				return Direction::Up;
			case Direction::Up:
				return Direction::Right;
			}
		}
		else
		{
			switch( _currentDirection )
			{
			case Direction::Right:
				return Direction::Up;
			case Direction::Down:
				return Direction::Right;
			case Direction::Left:
				return Direction::Down;
			case Direction::Up:
				return Direction::Left;
			}
		}
		throw std::logic_error( "Either turn or current direction has invalid value!" );
	}

	Position DirectionToOffset( Direction _direction )
	{
		switch( _direction )
		{
		case Direction::Right:
			return Position{ 1, 0 };
		case Direction::Down:
			return Position{ 0, 1 };
		case Direction::Left:
			return Position{ -1, 0 };
		case Direction::Up:
			return Position{ 0, -1 };
		}

		throw std::logic_error( "Direction value not handled!" );
	}
}

std::string
Result::FinishPartOne( )
{
	auto [m_columnsContinuations, m_rowsContinuations] = AnalyzeMap( m_map );
	PositionAndDirection position{ { m_rowsContinuations[ 0 ].first, 0 }, Direction::Right }; // we can use the continuations' data to get initial position
	Actions actions = GetActions( m_pathToFollow );

	for( const Action action : actions )
		position = PerformAction( m_map, position, action );

	return std::to_string( 1000 * ( position.m_position.m_row + 1 ) + 4 * ( position.m_position.m_col + 1 ) + DirectionValue( position.m_direction ) );
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

	// handle case when number is last item
	if( isNumber )
		result.push_back( number );

	return result;
}

Position operator+( const Position& _lhs, const Position& _rhs )
{
	return Position{ _lhs.m_col + _rhs.m_col, _lhs.m_row + _lhs.m_row };
}

PositionAndDirection
Result::PerformAction( const BoardMap& _map, PositionAndDirection _position, Action _action )
{
	auto TestPosition = [&_map]( const Position& _position ) -> TestPositionResult
		{
			if( _position.m_row < 0 || _position.m_row >= _map.size( ) )
				return TestPositionResult::OutsideMap;

			// UNDONE
		};


	if( std::holds_alternative<Turn>( _action ) )
	{
		Turn turn = std::get<Turn>( _action );
		if( turn == Turn::Right )
			_position.m_direction = MakeTurn( turn, _position.m_direction );
		else
		{
			const Position offset = DirectionToOffset( _position.m_direction );
			const bool isHorizontalMovement = { offset.m_col != 0 };

			while( true )
			{
				Position candidatePosition = _position.m_position + offset;
				TestPositionResult testResults = TestPosition( candidatePosition );

				// UNDONE
			}
		}

	}
	return _position;
}
