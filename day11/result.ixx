module;

#include <string>
#include <deque>
#include <map>

export module monkey_in_the_middle;

import AoC;

export namespace monkey_in_the_middle
{
	enum class OperationType
	{
		Multiplication,
		Addition,
		Square
	};

	class Monkey
	{
	private:
		std::deque<uint64_t>     m_items;
		OperationType            m_operationType;
		unsigned int             m_operationOperand;
		unsigned int             m_testValue;
		unsigned int             m_recipientIfTrue;
		unsigned int             m_recipientIfFalse;

		unsigned int             m_performedInspects;

	public:
		static unsigned int      m_commonMultiple;
		static void Init( );
		void ParseLine( const std::string& line );
		void ShowInfo( ) const;
		bool InspectNextItem( uint64_t& item, size_t& recipient, bool isPartOne );
		void PerformOperation( uint64_t& value );
		void GiveItem( uint64_t item );

		unsigned int PerformedInspects( ) const { return m_performedInspects; }
	};

	class Result : public AoC::Result
	{
	protected:
		virtual void Init() override;

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data
		std::map<size_t, Monkey> m_monkeys;
		Monkey* m_currentMonkey = nullptr;

		[[nodiscard]] std::string FinishCommon( unsigned int iterations );
	};
}
