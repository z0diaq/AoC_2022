export module grove_positioning_system:result;

import :types;

import AoC;

import <string>;
import <vector>;

export namespace grove_positioning_system
{
	class Result : public AoC::Result
	{

	public:
		Result( )
		{
		}

		static Value
		Parse( std::string_view _data, const size_t _rowNumber );

		static Values
		Mix( const Values& _initialValues );

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
		}

	private:
		//data
		Values m_values;
	};
}
