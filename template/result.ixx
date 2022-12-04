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

	protected:
		virtual void Init( ) override;

		virtual void ProcessOne( const std::string& data ) override;
		virtual uint64_t FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual uint64_t FinishPartTwo( ) override;

		virtual void Teardown( ) override;

	private:
		//data
	};
}
