module;

#include <string>
#include <vector>
#include <map>

export module pyroclastic_flow;
import :rock_shape;
import :rock;
import :rocks_tower;
import :jet_pattern;

import AoC;

export namespace pyroclastic_flow
{
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
		RocksTower               m_tower;
		std::vector<RockShape>   m_shapes;
		JetPattern               m_jetPattern;
		std::map<size_t, std::pair<size_t, size_t> > m_seenHashes;
		size_t                   m_skippedHeight = 0;


		void PrepareShapes( );

		void ProcessRock( Rock rock )
		{
			m_tower.PrepareForNewRock( rock );

			while( true )
			{
				m_jetPattern.Apply( rock, m_tower );
				if( false == rock.TryFall( m_tower ) )
				{
					rock.Rest( m_tower );
					return;
				}
			}
		}

		[[nodiscard]] Rock CreateRock( const size_t rockNo ) const;

		void DropRocks( size_t count );

		[[nodiscard]] size_t TowerHeight( ) const;
	};
}
