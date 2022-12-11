module;

#include <string>
#include <vector>

export module cathode_ray_tube;

import AoC;

export namespace cathode_ray_tube
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
		//data
		int m_reg = 1;

		unsigned int m_iteration = 1;
		unsigned int m_result = 0;

		//part 2 only
		std::vector<std::string> m_screen;

		void CheckIteration( );
	};
}
