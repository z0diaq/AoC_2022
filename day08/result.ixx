module;

#include <iostream>

export module treetop_tree_house;

import AoC;

export namespace treetop_tree_house
{
	class Result : public AoC::Result
	{
	protected:
		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override
		{
			m_treeMap.clear();
		}

	private:
		//data
		std::vector<std::string> m_treeMap;

	};
}
