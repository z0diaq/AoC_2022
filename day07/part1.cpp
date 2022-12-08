import no_space;

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

using namespace no_space;

std::string
Result::FinishPartOne()
{
	GatherSizes(&m_root["/"]);

	return std::to_string(GetSumOfDirectoriesSmallerThan100k(&m_root["/"]));
}

uint64_t
Result::GetSumOfDirectoriesSmallerThan100k(Node* node)
{
	if (node->m_type == Type::File)
		return 0;

	uint64_t sum{ 0 };
	for (auto& child : node->m_children)
		sum += GetSumOfDirectoriesSmallerThan100k(&child.second);

	if (node->m_size < 100'000)
		sum += node->m_size;

	return sum;
}

void
Result::ProcessOne( const std::string& data )
{
	ProcessGeneral(data);
}
