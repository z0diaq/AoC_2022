module;

#include <string>
#include <vector>

export module boiling_boulders:cube;

export namespace boiling_boulders
{
	class Cube
	{
		int m_x = 0;
		int m_y = 0;
		int m_z = 0;

	public:

		Cube( const std::string& row );
		Cube( int x, int y, int z );
		~Cube( ) = default;

		std::vector<Cube> PossibleNeighbours( ) const;

		void UpdateIfSmaller( const Cube& rhs );
		void UpdateIfBigger( const Cube& rhs );

		int X( ) const { return m_x; }
		int Y( ) const { return m_y; }
		int Z( ) const { return m_z; }
	};

	bool operator<( const Cube& lhs, const Cube& rhs );
}
