import tuning_trouble;

#include <iostream>
#include <string>

#include <map>

using namespace tuning_trouble;

void
Result::ProcessOne( const std::string& data )
{
	FindMarkerPosition(data, 4);
}

void
Result::ProcessTwo( const std::string& data )
{
	FindMarkerPosition(data, 14);
}

void
Result::FindMarkerPosition(const std::string& data, uint32_t windowSize)
{
	std::map<char, int> ocurrences;
	
	for (size_t from = 0, to = 0; to != data.length(); ++to)
	{
		char incoming = data[to];
		++ocurrences[incoming];
		if (to - from == windowSize)
		{
			char leaving = data[from];
			if (--ocurrences[leaving] == 0)
				ocurrences.erase(leaving);
			++from;
		}

		if (ocurrences.size() == windowSize)
		{
			m_startOfPacket = to + 1;
			break;
		}
	}
}

std::string
Result::FinishPartOne( )
{
	return std::to_string( m_startOfPacket );
}

std::string
Result::FinishPartTwo( )
{
	return std::to_string(m_startOfPacket);
}