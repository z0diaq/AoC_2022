module;

#include <string>
#include <map>
#include <set>
#include <vector>

export module regolith_reservoir:scan;

export constexpr char ROCK = '#';
export constexpr char SAND = 'o';
export constexpr char AIR = '.';

export namespace regolith_reservoir
{
	struct Point
	{
		int m_x = 0;
		int m_y = 0;
	};

	bool operator==( const Point& lhs, const Point& rhs )
	{
		return lhs.m_y == rhs.m_y &&
			lhs.m_x == rhs.m_x;
	}

	struct Range
	{
		int m_min = 0;
		int m_max = 0;

		Range( int initialValue ) :
			m_min( initialValue ),
			m_max( initialValue )
		{
		}

		int Length( ) const
		{
			return m_max - m_min;
		}

		bool IsOutside( const int value ) const
		{
			return value < m_min || value > m_max;
		}

		void Update( const int value )
		{
			m_min = std::min( value, m_min );
			m_max = std::max( value, m_max );
		}
	};

	enum class DropResult
	{
		Unknown,
		Blocked,
		FoundRestingPlace,
		FallenIntoAbyss,//part 1
		BlockedAtStart//part 2
	};

	class Scan
	{
		bool m_haveFloor = false;
		int m_floorLevel = 0;

		std::map<int, std::set<int> > m_rawMap;
		std::vector<std::string> m_areaScan;
		Range m_rangeX;
		Range m_rangeY;

	public:
		Scan( );

		void Reset( );

		void Process( const std::vector<Point>& path );

		void BeforeCompute( bool addInifiniteFloor = false );

		char& Get( const Point& pt );

		char Get( const Point& pt ) const;

		void SetRock( const Point& pt );

		void RestSand( const Point& pt );

		bool IsOutside( const Point& pt ) const;

		bool IsFree( const Point& pt ) const;

		void BlockPath( Point from, Point to );

		DropResult DropSand( );
	};
}
