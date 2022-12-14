module;

#include <iostream>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/classification.hpp>

export module camp_cleanup;

import AoC;

export namespace camp_cleanup
{
	class Result : public AoC::Result
	{
	protected:
		virtual void Init( ) override { m_result = 0; }
		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override { return std::to_string( m_result ); }
		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override { return std::to_string( m_result ); }

	private:
		uint64_t m_result;
	};
}
