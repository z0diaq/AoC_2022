module;

#include <iostream>

export module aoc_template;

import AoC;

export namespace aoc_template
{
	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual void ProcessOne( const std::string& data ) override;
		virtual void ProcessTwo( const std::string& data ) override;
		virtual uint64_t Finish( ) override;
		virtual void Teardown( ) override;

	private:

		//part one section
		virtual uint64_t FinishPartOne( );

		//part two section
		virtual uint64_t FinishPartTwo( );
	};
}

using namespace aoc_template;

Result::Result( )
{
}

void
Result::Init( )
{
}

void
Result::ProcessOne( const std::string& data )
{
}

void
Result::ProcessTwo( const std::string& data )
{
}

uint64_t
Result::Finish( )
{
	return IsPartOne( ) ? FinishPartOne( ) : FinishPartTwo( );
}

void
Result::Teardown( )
{
}

uint64_t
Result::FinishPartOne( )
{
	return 0;
}

uint64_t
Result::FinishPartTwo( )
{
	return 0;
}
