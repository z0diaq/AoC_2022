module;

module pyroclastic_flow:jet_pattern;
import :rock;
import :rocks_tower;

using namespace pyroclastic_flow;

void
JetPattern::Apply( Rock& rock, const RocksTower& tower )
{
	const bool shiftLeft = ( m_pattern[ m_currentIndex++ % m_pattern.size( ) ] == '<' );

	if( shiftLeft )
		rock.TryMoveLeft( tower );
	else
		rock.TryMoveRight( tower );
}
