module;

#include <string>
#include <map>
#include <set>

export module rope_bridge;

import AoC;

export namespace rope_bridge
{

	typedef std::pair<int, int> Position;

	std::ostream& operator<<( std::ostream& o, const Position& pos );


	class Result : public AoC::Result
	{

	public:
		Result();

	protected:
		virtual void Init() override;

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data

		std::map<int, std::set<int> > m_visitedPoints;

		//Position m_head;
		//Position m_tail;
		std::vector<Position> m_knots;

		[[ nodiscard ]] bool MoveTail( const Position& head, Position& tail ) const;
		void CheckTail( const Position& tail );
		void DumpVisitedPoints( );
	};
}
