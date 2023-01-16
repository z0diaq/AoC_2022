module;

#include <vector>
#include <optional>
#include <deque>

export module distress_signal:item;

export namespace distress_signal
{
	enum class ItemType
	{
		ListOpen,
		ListClose,
		Number
	};

	struct Item
	{
		ItemType                    m_type;
		std::optional<unsigned int> m_number;

		bool
		IsNumber( unsigned int& number ) const;

		bool
		IsListOpen( ) const;

		bool
		IsListClose( ) const;
	};

}
