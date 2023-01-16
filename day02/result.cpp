import rock_paper_scissors;

#include <stdexcept>
#include <string>

using namespace rock_paper_scissors;

void
Result::Init( )
{
	m_winConditions[ 0 ] = { 'A', 'B' };
	m_winConditions[ 1 ] = { 'B', 'C' };
	m_winConditions[ 2 ] = { 'C', 'A' };

	m_totalPoints = 0;
}

void
Result::ProcessGeneral( const std::string& data )
{
	if( data.length( ) != 3 )
		throw std::logic_error( "Unexpected length on input" );

	m_totalPoints += ComputeScore( DecodeGuide( { data[ 0 ], data[ 2 ] } ) );
}

std::string
Result::FinishGeneral( ) const
{
	return std::to_string( m_totalPoints );
}

Guide
Result::DecodeGuide( const Guide& guide ) const
{
	char decodedResponse{ 0 };
	if( IsPartOne( ) )
	{
		switch( guide.m_ourMove )
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
		if( guide.m_ourMove == 'Y' )
			decodedResponse = guide.m_opponentMove;
		else if( guide.m_ourMove == 'Z' )
		{
			for( auto winEntry : m_winConditions )
				if( winEntry.m_opponentMove == guide.m_opponentMove )
					decodedResponse = winEntry.m_ourMove;
		}
		else
		{
			//loose condition - find entry in win conditions by matching 'response' part
			for( auto winEntry : m_winConditions )
				if( guide.m_opponentMove == winEntry.m_ourMove )
					decodedResponse = winEntry.m_opponentMove;
		}
	}

	return { guide.m_opponentMove, decodedResponse };
}

uint32_t
Result::ComputeScore( const Guide& guide ) const
{
	const bool isWin = ( std::find( m_winConditions.begin( ), m_winConditions.end( ), guide ) != m_winConditions.end( ) );
	const bool isDraw = ( guide.m_opponentMove == guide.m_ourMove );

	uint32_t score = 0;

	if( isWin )
		score = 6;
	else if( isDraw )
		score = 3;

	return score + ( guide.m_ourMove - 'A' + 1 );
}
