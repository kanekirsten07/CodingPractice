#pragma once
#include <memory>
class SharedPtrNode
{
public:
	int data;
	std::shared_ptr<SharedPtrNode> left;
	std::shared_ptr<SharedPtrNode> right;

	SharedPtrNode(int d)
	{
		data = d;
		left = nullptr;
		right = nullptr;
	}
	void insertNode(std::shared_ptr<SharedPtrNode> value);
	void binaryInsertNode(std::shared_ptr<SharedPtrNode> value);
	void printTree();
};


