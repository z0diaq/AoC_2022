export module monkey_map:types;

import <vector>;
import <string>;
import <variant>;
import <map>;

export namespace monkey_map
{
	//module wide types go here
	typedef std::vector<std::string> MapData;
	typedef std::vector<std::pair<int, int>> Continuations;
	struct BoardMap
	{
		MapData m_data;
		Continuations m_rowsContinuations;
		Continuations m_columnsContinuations;
	};
	enum class Direction { Right, Down, Left, Up };

	struct Position
	{
		int m_col;
		int m_row;
	};

	Position operator+( const Position& _lhs, const Position& _rhs )
	{
		return Position{ _lhs.m_col + _rhs.m_col, _lhs.m_row + _rhs.m_row };
	}

	struct PositionAndDirection
	{
		Position m_position;
		Direction m_direction;
	};

	enum class TestPositionResult { Free, Blocked, OutsideMap };

	enum class Turn { Left, Right };
	typedef std::variant<int, Turn> Action;
	typedef std::vector<Action> Actions;
}
