import supply_stack;

#include <iostream>
#include <string>
#include <algorithm>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

using namespace supply_stack;

void
Result::ProcessGeneral(const std::string& data)
{
	if (data.empty())//spacing between 'stacks info' and 'rearrangement commands'
		return;

	if (false == (TryProcessStacksInfo(data) != TryProcessStacksRearrangeCommand(data)))
		throw std::logic_error( "Data incorrectly processed!");
}

bool
Result::TryProcessStacksInfo(const std::string& stacksInfoScanline)
{
	if (stacksInfoScanline.front( ) == '[' || stacksInfoScanline.front( ) == ' ')
	{
		const size_t stacks = (stacksInfoScanline.length() + 1) / 4;
		m_stacks.resize(stacks);

		if (stacksInfoScanline[ StackPositionInScanline( 0 )] == '1')//stacks numbering - ignore
			return true;

		for (size_t stack = 0; stack != stacks; ++stack)
		{
			const char c = stacksInfoScanline[ StackPositionInScanline( stack )];
			if (c != ' ')
				m_stacks[stack].push_front( c );
		}
		return true;
	}
	return false;
}

bool
Result::TryProcessStacksRearrangeCommand(const std::string& command)
{
	if ('m' == command.front())
	{
		std::vector<std::string> tokens;
		boost::split(tokens, command, boost::is_any_of(" "));

		if (tokens.size() != 6)
			throw std::logic_error("Unexpected count of tokens");

		uint32_t
			numberOfItems = boost::lexical_cast< uint32_t >(tokens[1]),
			from = boost::lexical_cast< uint32_t >(tokens[3]),
			to = boost::lexical_cast< uint32_t >(tokens[5]);

		RearrangeCommand(m_stacks[ from - 1 ], m_stacks[ to - 1 ], numberOfItems, IsPartOne());
		return true;
	}
	return false;
}

void
Result::RearrangeCommand(Stack& fromStack, Stack& toStack, size_t count, bool isOldCrateMover)
{
	if (isOldCrateMover)
	{
		std::ranges::move(
			fromStack.rbegin(), fromStack.rbegin() + count,
			std::back_inserter(toStack));
	}
	else
	{
		std::ranges::move(
			fromStack.begin() + (fromStack.size( ) - count ), fromStack.end(),
			std::back_inserter(toStack));

	}
	fromStack.resize(fromStack.size() - count);//std::ranges::move moves items but does not shrink container
}

void
Result::Teardown()
{
	m_stacks.clear();
}

std::string
Result::FinishGeneral() const
{
	std::string result;
	std::transform(
		m_stacks.begin(),
		m_stacks.end(),
		std::back_inserter(result),
		[](const Stack& stack) -> char
		{
			return stack.back();
		});
	return result;
}
