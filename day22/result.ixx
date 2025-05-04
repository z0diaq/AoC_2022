export module monkey_map:result;

import :types;

import AoC;

import <string>;

export namespace monkey_map
{
	namespace tests
	{
		class AnalyzeMapDataTest;
		class GetActionsTest;
	}

	class Result : public AoC::Result
	{
		friend class tests::AnalyzeMapDataTest;
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
			m_map.m_data.clear( );
			m_map.m_columnsContinuations.clear( );
			m_map.m_rowsContinuations.clear( );
			m_pathToFollow.clear( );
		}

		static std::tuple<Continuations, Continuations>
		AnalyzeMapData( const MapData& _mapData );

		static Actions
		GetActions( const std::string& _pathToFollow );

		static PositionAndDirection
		PerformAction( const BoardMap& _map, PositionAndDirection _position, Action _action );

	private:
		BoardMap m_map;
		std::string m_pathToFollow;
	};
}
