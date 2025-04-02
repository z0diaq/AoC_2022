module;

#include <string>
#include <vector>
#include <regex>

export module not_enough_minerals;
import :types;
import :blueprint;
export import :robot_cost;

export namespace not_enough_minerals
{
	class Result : public AoC::Result
	{

	protected:
		virtual void Init( ) override;

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data
		std::regex m_lineRegex;
		std::vector<Blueprint> m_blueprints;

		void Process( const std::string& data );
		size_t MostGeodesCollected( const Blueprint& bp, size_t timeLimit ) const;
		bool ShouldBuild( const State& state, Type type, const Blueprint& bp ) const;
		bool BlockIfEnoughRobots( State& state, const Blueprint& bp ) const;
	};
}
