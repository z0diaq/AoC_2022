import no_space;

#include <string>

using namespace no_space;

std::string
Result::FinishPartTwo()
{
	GatherSizes(&m_root["/"]);

	const uint64_t totalSpace = 70'000'000,
		requiredSpace = 30'000'000,
		totalOccupied = m_root["/"].m_size;

	uint64_t dirSizeToDelete = std::numeric_limits<uint64_t>::max();

	FindBestDirToDelete(dirSizeToDelete,
	                    &m_root["/"],
	                    requiredSpace - (totalSpace - totalOccupied));

	return std::to_string(dirSizeToDelete);
}

void
Result::FindBestDirToDelete(uint64_t& dirSizeToDelete, Node* node, const uint64_t requiredSpaceToFree)
{
	if (node->m_type == Type::File)
		return;

	for (auto& child : node->m_children)
		FindBestDirToDelete(dirSizeToDelete, &child.second, requiredSpaceToFree);

	if (node->m_size >= requiredSpaceToFree && node->m_size < dirSizeToDelete)
		dirSizeToDelete = node->m_size;
}

void
Result::ProcessTwo(const std::string& data)
{
	ProcessGeneral(data);
}
