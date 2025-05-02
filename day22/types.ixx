export module monkey_map:types;

import <vector>;
import <string>;
import <variant>;

export namespace monkey_map
{
	//module wide types go here
	typedef std::vector<std::string> BoardMap;
	typedef std::vector<std::pair<int, int>> Continuations;
	typedef std::pair<int, int> Position;

	enum class Turn { Left, Right };
	typedef std::variant<int, Turn> Action;
	typedef std::vector<Action> Actions;
}
