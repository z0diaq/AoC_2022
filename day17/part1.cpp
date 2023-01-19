import pyroclastic_flow;

#include <string>

using namespace pyroclastic_flow;

void
Result::ProcessOne( const std::string& data )
{
	m_jetPattern.m_pattern = data;
}

std::string
Result::FinishPartOne( )
{
	this->DropRocks( 2'022 );
	return std::to_string( this->TowerHeight( ) );
}
