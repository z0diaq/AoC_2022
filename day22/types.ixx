export module monkey_map:types;

import <vector>;
import <string>;
import <variant>;
import <map>;

export namespace monkey_map
{
	//module wide types go here
	typedef std::vector<std::string> BoardMap;
	typedef std::vector<std::pair<int, int>> Continuations;
	enum class Direction { Right, Down, Left, Up };

	struct Position
	{
		int m_row;
		int m_col;
	};

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
