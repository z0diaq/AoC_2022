module;

#include <iostream>
#include <deque>

export module supply_stack;

import AoC;

export namespace supply_stack
{
	class Result : public AoC::Result
	{
	protected:

		virtual void ProcessOne(const std::string& data) override { return ProcessGeneral( data ); }
		virtual std::string FinishPartOne() override              { return FinishGeneral(); }

		virtual void ProcessTwo(const std::string& data) override { return ProcessGeneral( data ); }
		virtual std::string FinishPartTwo() override              { return FinishGeneral(); }

		virtual void Teardown( ) override;

	private:

		typedef std::deque<char> Stack;
		std::vector<Stack>       m_stacks;

		void ProcessGeneral(const std::string& data);
		std::string FinishGeneral() const;

		bool TryProcessStacksInfo(const std::string& stacksInfoScanline);
		bool TryProcessStacksRearrangeCommand(const std::string& command);
		void RearrangeCommand(Stack& fromStack, Stack& toStack, size_t count, bool isOldCrateMover);
		size_t StackPositionInScanline(size_t stackNo) const      { return stackNo * 4 + 1; }
	};
}
