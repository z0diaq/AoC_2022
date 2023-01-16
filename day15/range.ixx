module;

#include <algorithm>

export module beacon_exclusion_zone:scan;

export namespace beacon_exclusion_zone
{

	struct Range
	{
		int m_min = 0;
		int m_max = 0;

		Range( int min, int max ) :
			m_min( min ),
			m_max( max )
		{
		}

		bool Contains( int value ) const
		{
			return value >= m_min && value <= m_max;
		}

		bool TryMerge( const Range& rhs )
		{
			if( Contains( rhs.m_min ) )
			{
				m_max = std::max( m_max, rhs.m_max );
				return true;
			}
			else if( Contains( rhs.m_max ) )
			{
				m_min = std::min( m_min, rhs.m_min );
				return true;
			}
			else
				return false;
		}

		int Size( ) const
		{
			return m_max - m_min;
		}
	};

	bool operator<( const Range& lhs, const Range& rhs )
	{
		return lhs.m_min < rhs.m_min;
	}
}
