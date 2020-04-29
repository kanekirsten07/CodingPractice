#include "SharedPtrNode.h"

#include "Node.h"
#include <iostream>


void SharedPtrNode::insertNode(std::shared_ptr<SharedPtrNode> value)
{
	if (nullptr == this->left)
	{
		this->left = value;
	}
	else if (nullptr == this->right)
	{
		this->right = value;
	}
	else
	{
		this->left->insertNode(value);
	}
}

void SharedPtrNode::binaryInsertNode(std::shared_ptr<SharedPtrNode> value)
{
	if (value->data < this->data)
	{
		if (nullptr == this->left)
		{
			this->left = value;
		}
		else
		{
			this->left->insertNode(value);
		}
	}
	else if (value->data > this->data)
	{
		if (nullptr == this->right)
		{
			this->right = value;
		}
		else
		{
			this->right->insertNode(value);
		}
	}
}



void SharedPtrNode::printTree()
{
	std::cout << this->data;
	if (nullptr != this->left)
	{
		this->left->printTree();
	}
	if (nullptr != this->right)
	{
		this->right->printTree();
	}
}