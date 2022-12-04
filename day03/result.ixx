module;

#include <iostream>
#include <algorithm>
#include <array>

export module rucksack_reorganization;

import AoC;

export namespace rucksack_reorganization
{
	class Result : public AoC::Result
	{

	public:
		virtual void Init( ) override;
		virtual void ProcessOne( const std::string& data ) override;
		virtual void ProcessTwo( const std::string& data ) override;
		virtual uint64_t Finish( ) override;
		virtual void Teardown( ) override { }

	private:

		uint64_t m_sum;

		std::string FindCommonSet( std::string lhs, std::string rhs )
		{
			std::string result;
			std::ranges::sort( lhs );
			std::ranges::sort( rhs );
			std::ranges::set_intersection( lhs, rhs, std::back_inserter( result ) );
			const auto [first, last] = std::ranges::unique( result.begin( ), result.end( ) );
			result.erase( first, last );
			return result;
		}

		char FindCommonItem( std::string lhs, std::string rhs )
		{
			auto result = FindCommonSet( lhs, rhs );
			if( result.size( ) != 1 )
				throw std::logic_error( "Unexpected size!" );
			return result[ 0 ];
		}

		uint64_t ComputeScore( char c ) const
		{
			if( c >= 'a' && 'c' <= 'z' )
				return c - 'a' + 1;
			else if( c >= 'A' && c <= 'Z' )
				return c - 'A' + 27;
			throw std::logic_error( "Unexpected char" );
		}

		//part one section
		virtual uint64_t FinishPartOne( ) const;

		//part two section
		uint32_t m_gatheredItems = 0;
		std::array< std::string, 3 > m_groupData;
		virtual uint64_t FinishPartTwo( ) const;
	};
}

using namespace rucksack_reorganization;

void
Result::Init( )
{
	m_sum = 0;
}

void
Result::ProcessOne( const std::string& data )
{
	auto middle = data.length( ) / 2;

	m_sum += ComputeScore( FindCommonItem( data.substr( 0, middle ), data.substr( middle ) ) );
}

void
Result::ProcessTwo( const std::string& data )
{
	m_groupData[ m_gatheredItems++ ] = data;

	if( m_gatheredItems == 3 )
	{
		char common = FindCommonItem(
			FindCommonSet(
				m_groupData[ 0 ], m_groupData[ 1 ] ),
			m_groupData[ 2 ] );
		m_sum += ComputeScore( common );
		m_gatheredItems = 0;
	}
}

uint64_t
Result::Finish( )
{
	return IsPartOne( ) ? FinishPartOne( ) : FinishPartTwo( );
}

uint64_t
Result::FinishPartOne( ) const
{
	return m_sum;
}

uint64_t
Result::FinishPartTwo( ) const
{
	return m_sum;
}