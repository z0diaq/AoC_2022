module;

#include <iostream>
#include <map>

export module no_space;

import AoC;

export namespace no_space
{
	enum class Type
	{
		Directory,
		File
	};

	struct Node;

	typedef std::map<std::string, Node> TreeNode;

	struct Node
	{
		Type      m_type;
		Node*     m_parent;// = ..
		uint64_t  m_size = 0;//either file size or all files sizes sum
		TreeNode  m_children;
	};

	class Result : public AoC::Result
	{
	protected:
		virtual void Init() override
		{
			m_currentDirectory = nullptr;
		}

		void ProcessGeneral(const std::string& data);

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override
		{
			m_root.clear();
		}

	private:
		//shared
		TreeNode m_root;
		Node*    m_currentDirectory;

		uint64_t GatherSizes(Node* node );

		//part1
		uint64_t GetSumOfDirectoriesSmallerThan100k(Node* node);

		//part2
		void FindBestDirToDelete(uint64_t& dirSizeToDelete, Node* node, const uint64_t requiredSpaceToFree);

	};
}
