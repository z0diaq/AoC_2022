import pyroclastic_flow;

#include <string>

using namespace pyroclastic_flow;

void
Result::ProcessTwo(const std::string& data)
{
	m_jetPattern.m_pattern = data;
}

std::string
Result::FinishPartTwo()
{
	this->DropRocks( 1'000'000'000'000ull );
	return std::to_string( this->TowerHeight( ) );
}
