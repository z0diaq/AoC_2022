export module monkey_math:result;

import :types;

import AoC;

import <string>;
import <unordered_map>;
import <optional>;

export namespace monkey_math
{
	class Result : public AoC::Result
	{

	public:
		Result( )
		{
		}

		static std::optional<std::pair<std::string, std::string> >
			ProcessLine( const std::string& _line );

		static std::int64_t Evaluate( const MonkeyMath& _monkeys, const std::string& _name );

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
		MonkeyMath m_monkeys;
	};
}
