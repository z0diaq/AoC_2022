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
		static Value
		Parse( std::string_view _data, const size_t _rowNumber );

		static Values
		Mix( const Values& _initialValues );

		static int64_t
		GetCoordinates( const Values& _mixedValues );

	protected:

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown( ) override
		{
			m_values.clear( );
		}

	private:
		Values m_values;
	};
}
