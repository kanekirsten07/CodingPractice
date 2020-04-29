#include "Node.h"
#include <iostream>

void Node::insertNode(Node* value)
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

void Node::printTree()
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