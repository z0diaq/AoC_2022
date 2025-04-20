export module monkey_math:result;

import :types;

import AoC;

import <string>;
import <unordered_map>;

export namespace monkey_math
{
	class Result : public AoC::Result
	{

	public:
		Result( )
		{
		}

	protected:
		virtual void Init( ) override
		{
		}

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown( ) override
		{
		}

	private:
		//data
		std::unordered_map<std::string, std::string> m_monkeys;
	};
}
