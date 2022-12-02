module;

#include <string>
#include <stdexcept>

export module rock_paper_scissors:data;

export import AoC;

export namespace rock_paper_scissors
{
	struct Data : public AoC::Data
	{
		typedef std::pair<char, char> GuideEntry;
		GuideEntry m_entry;

		virtual void Process( const std::string& line ) override;
		virtual void Reset( ) override;
	};
}

using namespace rock_paper_scissors;

void
Data::Process( const std::string& line )
{
	if( line.length( ) != 3 )
		throw std::logic_error( "Unexpected length on input" );
	m_entry.first = line[ 0 ];
	m_entry.second = line[ 2 ];
}

void
Data::Reset( )
{
}
