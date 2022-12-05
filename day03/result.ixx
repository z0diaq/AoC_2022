module;

#include <array>
#include <string>

export module rucksack_reorganization;

import AoC;

export namespace rucksack_reorganization
{
	class Result : public AoC::Result
	{

	protected:
		virtual void Init( ) override;
		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override { return std::to_string( m_sum ); }
		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override { return std::to_string( m_sum ); }
		virtual void Teardown( ) override { }

	private:
		uint64_t                     m_sum;
		uint32_t                     m_gatheredItems = 0;
		std::array< std::string, 3 > m_groupData;

		std::string FindCommonSet( std::string lhs, std::string rhs );
		char        FindCommonItem( std::string lhs, std::string rhs );
		uint64_t    ComputeScore( char c ) const;

	};
}
