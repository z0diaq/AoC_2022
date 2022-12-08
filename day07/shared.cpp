import no_space;

#include <string>

#include <boost/lexical_cast.hpp>

using namespace no_space;

uint64_t
Result::GatherSizes(Node* node)
{
	if (node->m_type == Type::File)
		return node->m_size;

	node->m_size = 0;

	for (auto& child : node->m_children)
		node->m_size += GatherSizes(&child.second);

	return node->m_size;
}

void
Result::ProcessGeneral(const std::string& data)
{
	if (data[0] == '$')
	{
		if (data.substr(0, 4) == "$ cd")
		{
			std::string dirName = data.substr(5);

			if (dirName == "..")
				m_currentDirectory = m_currentDirectory->m_parent;
			else
			{
				if (m_currentDirectory == nullptr)
				{
					m_root[dirName] = { Type::Directory, nullptr };
					m_currentDirectory = &m_root[dirName];
				}
				else
				{
					(*m_currentDirectory).m_children[dirName] = { Type::Directory, m_currentDirectory };
					m_currentDirectory = &(*m_currentDirectory).m_children[dirName];
				}
			}
		}
	}
	else
	{
		//ls output
		if (data.substr(0, 4) != "dir ")
		{
			const auto pos = data.find(' ');
			const uint64_t fileSize = boost::lexical_cast< uint64_t >(data.substr(0, pos));
			const std::string filename = data.substr(pos + 1);

			m_currentDirectory->m_children[filename] = { Type::File, m_currentDirectory, fileSize };
		}
	}
}
