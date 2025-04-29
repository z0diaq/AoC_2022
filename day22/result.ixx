export module monkey_map:result;

import :types;

import AoC;

import <string>;

export namespace monkey_map
{
	class Result : public AoC::Result
	{

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
		}

	private:
		//data
		BoardMap m_map;
		std::string m_pathToFollow;
	};
}
