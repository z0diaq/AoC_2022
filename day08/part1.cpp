import treetop_tree_house;

#include <iostream>
#include <string>
#include <vector>

using namespace treetop_tree_house;

void
Result::ProcessOne( const std::string& data )
{
	m_treeMap.push_back(data);
}

std::string
Result::FinishPartOne( )
{
	const int width = static_cast<int>(m_treeMap[0].length());
	const int height = static_cast<int>(m_treeMap.size());

	std::vector<std::vector<bool> > visible;

	for (int row = 0; row != height; ++row)
		visible.push_back(std::vector<bool>(width, false));

	auto CheckTreesInLine = [this, &visible](int row, const int rowEnd, const int rowStep,
	                                                                int col, const int colEnd, const int colStep) -> void
	{
		char tallestTreeInLine = m_treeMap[row][col];
		visible[row][col] = true;

		int& pos = (rowStep ? row : col);//attach to either row or col
		const int posEnd = (rowStep ? rowEnd : colEnd);
		const int step = (rowStep ? rowStep : colStep);
		for (; pos != posEnd + step; pos += step)
		{
			char treeHeight = m_treeMap[row][col];
			if (treeHeight > tallestTreeInLine)
			{
				tallestTreeInLine = treeHeight;
				visible[row][col] = true;
			}
		}
	};
	
	//scan columns
	for (int row = 0; row < height; ++row)
	{
		CheckTreesInLine(row, row, 0, //in single row...
		                 0, width-1, 1);//...check all columns from left to right
		CheckTreesInLine(row, row, 0,//in single row...
		                 width - 1, 0, -1);//...check all columns from right to left
	}

	//scan rows
	for (int col = 0; col < width; ++col)
	{
		CheckTreesInLine(0, width-1, 1,//check all rows from top to bottom...
		                 col, col, 0); //...from single column
		CheckTreesInLine(width-1, 0, -1,//check all rows from bottom to top...
		                 col, col, 0); //...from single column
	}

	int result = 0;
	for (int row = 0; row < height; ++row)
		for (int col = 0; col < width; ++col)
			if (visible[row][col])
				++result;

	return std::to_string( result );
}
