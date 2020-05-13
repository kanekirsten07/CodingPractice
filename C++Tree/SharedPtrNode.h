#pragma once
#include <memory>
class SharedPtrNode
{
public:
	int data;
	bool visited;
	std::shared_ptr<SharedPtrNode> left;
	std::shared_ptr<SharedPtrNode> right;

	SharedPtrNode(int d)
		:data(d)
	{
		visited = false;
	}
	void insertNode(const std::shared_ptr<SharedPtrNode>& value);
	void binaryInsertNode(const std::shared_ptr<SharedPtrNode>& value);
	void printTreeDepthFirst();
	void printTreeBreadthFirst();
};


