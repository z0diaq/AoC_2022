export module monkey_map:types;

import <vector>;
import <string>;
//import <pair>;

export namespace monkey_map
{
	//module wide types go here
	typedef std::vector<std::string> BoardMap;
	typedef std::vector<std::pair<int, int>> Continuations;
}
