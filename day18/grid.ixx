module;

#include <set>

export module boiling_boulders:grid;

import :cube;

export namespace boiling_boulders
{
	class Grid
	{
	private:
		std::set<Cube> m_droplets;

	public:
		void Add( const Cube& newCube );
		void Reset( );

		[[nodiscard]] size_t NeighboursCount( const Cube& cube ) const;

		[[nodiscard]] size_t ComputeOutsideArea( ) const;

		[[nodiscard]] std::pair<Cube, Cube> FindContainingBox( int extraSpace = 1 ) const;

		[[nodiscard]] Grid NegativeImage( Cube& minValue ) const;

		void RemoveConnectedCubes( const Cube& cube );

	};
}
