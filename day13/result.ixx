module;

#include <string>

export module distress_signal;
export import :packet;
export import :extractor;

import AoC;

export namespace distress_signal
{
	class Result : public AoC::Result
	{

	protected:
		virtual void Init() override;

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data
		std::vector<Packet> m_packets;
		size_t m_inRightOrder = 0;

		void ProcessNewPacketData( const std::string& data );
	};
}
