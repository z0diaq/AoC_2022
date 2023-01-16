import distress_signal;

using distress_signal::Item;

bool
Item::IsNumber( unsigned int& number ) const
{
	if( m_type == ItemType::Number )
	{
		number = m_number.value( );
		return true;
	}

	return false;
}

bool
Item::IsListOpen( ) const
{
	return m_type == ItemType::ListOpen;
}

bool
Item::IsListClose( ) const
{
	return m_type == ItemType::ListClose;
}
