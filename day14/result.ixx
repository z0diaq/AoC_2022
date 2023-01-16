module;

#include <string>

export module regolith_reservoir;
export import :scan;

import AoC;

export namespace regolith_reservoir
{
	typedef unsigned short u_short;

	class Result : public AoC::Result
	{
	protected:
		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		Scan m_scan;

		void Process( const std::string& data );
	};
}
