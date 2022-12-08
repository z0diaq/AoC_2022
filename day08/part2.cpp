import treetop_tree_house;

#include <iostream>
#include <string>
#include <vector>

using namespace treetop_tree_house;

void
Result::ProcessTwo(const std::string& data)
{
	ProcessOne(data);
}

std::string
Result::FinishPartTwo()
{
	const int width = static_cast< int >(m_treeMap[0].length()),
		height = static_cast< int >(m_treeMap.size());

	auto ComputeScenicScore = [this, width, height](const int row, const int col) -> int
	{
		if (col == 0 || row == 0 || col == width - 1 || row == height - 1)
			return 0;//edge is not interesting since they will always produce 0 as result...

		const char myHeight = m_treeMap[row][col];

		int minCol = col - 1,
			maxCol = col + 1,
			minRow = row - 1,
			maxRow = row + 1;

		for (; minCol > 0; --minCol)
			if (m_treeMap[row][minCol] >= myHeight)
				break;

		for (; maxCol < width - 1; ++maxCol)
			if (m_treeMap[row][maxCol] >= myHeight)
				break;

		for (; minRow > 0; --minRow)
			if (m_treeMap[minRow][col] >= myHeight)
				break;

		for (; maxRow < height - 1; ++maxRow)
			if (m_treeMap[maxRow][col] >= myHeight)
				break;

		return (row - minRow) * (maxRow - row) * (col - minCol) * (maxCol - col);
	};

	int result = 0;
	for (int row = 0; row < height; ++row)
		for (int col = 0; col < width; ++col)
			result = std::max(result, ComputeScenicScore(row, col));

	return std::to_string(result);
}