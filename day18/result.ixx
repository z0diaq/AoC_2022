module;

#include <string>

export module boiling_boulders;
import :cube;
import :grid;

import AoC;

export namespace boiling_boulders
{
	class Result : public AoC::Result
	{

	protected:
		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		Grid m_grid;

		void Process( const std::string& data );

		[[nodiscard]] size_t OutsideArea( ) const;
		[[nodiscard]] size_t InsideArea( ) const;
	};
}
