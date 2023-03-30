module;

// any includes ?

module not_enough_minerals:robot_cost;

using not_enough_minerals::RobotCost;

RobotCost::RobotCost( size_t ore, size_t clay, size_t obsidian ) :
	m_cost{ ore, clay, obsidian, 0 }
{
}

bool
RobotCost::Consume( MineralsQuantity& gathered ) const
{
	for( int type = Ore; type != Geode; ++type )
	{
		if( gathered[ type ] < m_cost[ type ] )
			return false;
	}

	gathered[ Ore ] -= m_cost[ Ore ];
	gathered[ Clay ] -= m_cost[ Clay ];
	gathered[ Obsidian ] -= m_cost[ Obsidian ];

	return true;
}

bool
RobotCost::EnoughMinerals( const MineralsQuantity& gathered ) const
{
	for( int type = Ore; type != Geode; ++type )
	{
		if( gathered[ type ] < m_cost[ type ] )
			return false;
	}
	return true;
}

size_t
RobotCost::Cost( int type ) const
{
	return m_cost[ type ];
}

bool
RobotCost::HaveRequiredMinerals( const MineralsQuantity& providedMinerals ) const
{
	for( int type = 0; type != 4; ++type )
		if( m_cost[ type ] && providedMinerals[ type ] == 0 )
			return false;
	return true;
}
