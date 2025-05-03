export module monkey_map:result;

import :types;

import AoC;

import <string>;

export namespace monkey_map
{
	namespace tests
	{
		class AnalyzeMapTest;
		class GetActionsTest;
	}

	class Result : public AoC::Result
	{
		friend class tests::AnalyzeMapTest;
		friend class tests::GetActionsTest;

	public:
		Result( )
		{
		}

	protected:
		virtual void Init( ) override
		{
		}

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown( ) override
		{
			m_map.clear( );
			m_pathToFollow.clear( );

			m_rowsContinuations.clear( );
			m_columnsContinuations.clear( );
		}

		static std::tuple<Continuations, Continuations>
		AnalyzeMap( const BoardMap& _map );

		static Actions
		GetActions( const std::string& _pathToFollow );

		static PositionAndDirection
		PerformAction( const BoardMap& _map, PositionAndDirection _position, Action _action );

	private:
		BoardMap m_map;
		std::string m_pathToFollow;
		Continuations m_rowsContinuations;
		Continuations m_columnsContinuations;
	};
}
