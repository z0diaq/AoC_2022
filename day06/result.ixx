module;

#include <iostream>

export module tuning_trouble;

import AoC;

export namespace tuning_trouble
{
	class Result : public AoC::Result
	{
	protected:

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

	private:
		//data
		size_t m_startOfPacket = 0;
		void FindMarkerPosition(const std::string& data, uint32_t windowSize);
	};
}
