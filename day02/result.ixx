module;

#include <iostream>
#include <array>

export module rock_paper_scissors;

import AoC;

export namespace rock_paper_scissors
{
	struct Guide
	{
		char m_opponentMove;
		char m_ourMove;

		bool operator==( const Guide& rhs ) const
		{
			return m_opponentMove == rhs.m_opponentMove &&
				m_ourMove == rhs.m_ourMove;
		}
	};

	class Result : public AoC::Result
	{

	protected:
		virtual void Init( ) override;
		virtual void ProcessOne( const std::string& data ) { ProcessGeneral( data ); }
		virtual std::string FinishPartOne( ) override { return FinishGeneral( ); }
		virtual void ProcessTwo( const std::string& data ) { ProcessGeneral( data ); }
		virtual std::string FinishPartTwo( ) override { return FinishGeneral( ); }
		virtual void Teardown( ) override { }

	private:

		std::array<Guide, 3> m_winConditions;
		uint32_t             m_totalPoints;

		void ProcessGeneral( const std::string& data );
		std::string FinishGeneral( ) const;

		Guide DecodeGuide( const Guide& guide ) const;
		uint32_t ComputeScore( const Guide& guiide ) const;
	};
}
