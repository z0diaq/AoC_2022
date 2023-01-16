module;

#include <string>
#include <map>
#include <ranges>
#include <set>

export module proboscidea_volcanium;
export import :valve_info;
export import :min_distances;

import AoC;

export namespace proboscidea_volcanium
{
	class Result : public AoC::Result
	{

	protected:
		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:

		std::map<std::string, ValveInfo> m_valves;
		std::map<std::string, uint> m_analyzedFlows;
		MinDistances m_minDistances;

		void Process( const std::string& data );
		void Prepare( );
		void AddScanline( const std::string& name, unsigned int flowRate, const std::vector<Connection>& connections );
		void Remove( const std::string& name );
		void Connect( const std::string& from, const std::string& to, const uint distance );
		void CreateNewConnections( const std::vector<Connection>& connections );
		void RemoveDummyValves( );
		void SetIndexes( );

		uint Index( const std::string& name ) const;
		uint Distance( const std::string& from, const std::string& to ) const;
		uint ComputeBestCumulativeFlow( const std::string& currentLocation, std::set<std::string> availableValves, const uint remainingTime );
	};
}
