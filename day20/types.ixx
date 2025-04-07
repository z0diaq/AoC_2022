export module grove_positioning_system:types;

import <tuple>;
import <vector>;

export namespace grove_positioning_system
{
	//module wide types go here
	struct Value
	{
		int m_value;
		size_t m_position;

		[[nodiscard]] bool operator==( const Value& _rhs ) const
		{
			return std::tie( m_value, m_position ) == std::tie( _rhs.m_value, _rhs.m_position );
		}
	};

	using Values = std::vector<Value>;
}
