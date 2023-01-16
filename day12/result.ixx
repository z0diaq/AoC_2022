module;

#include <string>
#include <vector>

export module hill_climbing_algorithm;

import AoC;

export namespace hill_climbing_algorithm
{
	struct Location
	{
		size_t m_row = 0;
		size_t m_column = 0;

		bool operator<( const Location& rhs ) const
		{
			if( m_row < rhs.m_row )
				return true;
			else if( m_row > rhs.m_row )
				return false;

			return m_column < rhs.m_column;
		}
	};
	typedef std::vector<Location> Path;
	typedef std::vector<Location> LocationsList;

	class Result : public AoC::Result
	{
	protected:
		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		std::vector<std::string> m_heightMap;

		void Process( const std::string& data );

		unsigned int FindShortestPathLength( );
		LocationsList FindValidNeighbors( const Location& pos ) const;
		Location FindLocation( char c ) const;
		const char Value( const Location& loc ) const;
		bool IsValid( const Location& loc ) const;
	};
}
