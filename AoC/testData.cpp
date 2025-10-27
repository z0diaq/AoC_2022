module;

// Include all standard library headers in global module fragment (before importing)
#include <string>
#include <iostream>
#include <exception>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>

module AoC;

// Implementation file - no export needed
using AoC::TestData;

std::string Normalize( std::string data );

void
TestData::Load( const std::string& filename, const std::string& dataTag )
{
	fs::path path;

	if( AoC::FindFileInPredefinedLocations( filename, path, dataTag ) )
	{
		try
		{
			boost::split( m_data, Normalize( ReadFileContents( path ) ), boost::is_any_of( "\n" ) );
			m_expectedResultPart1 = ReadFileContents( GetPathVariant( path, DataType::RESULT_PART_1 ) );
			m_expectedResultPart2 = ReadFileContents( GetPathVariant( path, DataType::RESULT_PART_2 ) );
		}
		catch( std::exception& e )
		{
			std::cerr << "FATAL: exception [" << e.what( ) << "] caught while preparring data!" << std::endl;
		}
	}
}

std::string Normalize( std::string data )
{
	boost::replace_all( data, "\r\n", "\n" );
	return data;
}
