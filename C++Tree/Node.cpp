#include "Node.h"
#include <iostream>

void Node::insertNode(Node* value)
{
	if (nullptr == this->left)
	{
		left = value;
	}
	else if (nullptr == this->right)
	{
		right = value;
	}
	else
	{
		left->insertNode(value);
	}
}

void Node::printTree()
{
	std::cout << this->data;
	if (nullptr != this->left)
	{
		left->printTree();
	}
	if (nullptr != this->right)
	{
		right->printTree();
	}
} 