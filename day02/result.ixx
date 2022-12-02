module;

#include <iostream>
#include <array>

export module rock_paper_scissors;

export import :data;

export namespace rock_paper_scissors
{
	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual bool ProcessGeneral( const AoC::DataPtr& data ) override;
		virtual uint64_t Finish( ) const override;
		virtual void Teardown( ) override;

	private:

		std::array<Data::GuideEntry, 3> m_winConditions;
		uint32_t                        m_totalPoints;

		Data::GuideEntry DecodeGuide( const Data::GuideEntry& entry ) const;
		uint32_t ComputeScore( Data::GuideEntry entry ) const;
	};
}

using namespace rock_paper_scissors;

Result::Result( )
{
}

void
Result::Init( )
{
	m_data.reset( new rock_paper_scissors::Data( ) );
	m_haveDedicatedProcessing = false;

	m_winConditions[ 0 ] = { 'A', 'B' };
	m_winConditions[ 1 ] = { 'B', 'C' };
	m_winConditions[ 2 ] = { 'C', 'A' };

	m_totalPoints = 0;
}

void
Result::Teardown( )
{
	m_data.reset( );
	m_totalPoints = 0;
}

bool
Result::ProcessGeneral( const AoC::DataPtr& data )
{
	auto dataPtr = static_cast< Data* >( data.get( ) );

	m_totalPoints += ComputeScore( DecodeGuide( dataPtr->m_entry ) );

	return true;//drop data, we used all
}

uint64_t
Result::Finish( ) const
{
	std::cout
		<< "result = "
		<< m_totalPoints
		<< std::endl;

	return m_totalPoints;
}

Data::GuideEntry
Result::DecodeGuide( const Data::GuideEntry& entry ) const
{
	char decodedResponse;
	if( IsPartOne( ) )
	{
		switch( entry.second )
		{
		case 'X':
			decodedResponse = 'A';
			break;
		case 'Y':
			decodedResponse = 'B';
			break;
		case 'Z':
			decodedResponse = 'C';
			break;
		}
	}
	else
	{
		//X - loose
		//Y - draw
		//Z - win
		if( entry.second == 'Y' )
			decodedResponse = entry.first;
		else if( entry.second == 'Z' )
		{
			for( auto winEntry : m_winConditions )
				if( winEntry.first == entry.first )
					decodedResponse = winEntry.second;
		}
		else
		{
			//loose condition - find entry in win conditions by matching 'response' part
			for( auto winEntry : m_winConditions )
				if( entry.first == winEntry.second )
					decodedResponse = winEntry.first;
		}
	}

	return { entry.first, decodedResponse };
}

uint32_t
Result::ComputeScore( Data::GuideEntry entry ) const
{
	const bool isWin = ( std::find( m_winConditions.begin( ), m_winConditions.end( ), entry ) != m_winConditions.end( ) );
	const bool isDraw = ( entry.first == entry.second );

	uint32_t score = 0;

	if( isWin )
		score = 6;
	else if( isDraw )
		score = 3;

	return score + ( entry.second - 'A' + 1 );
}
