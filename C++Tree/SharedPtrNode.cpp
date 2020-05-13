#include "SharedPtrNode.h"

#include "Node.h"
#include <iostream>
#include <queue>


void SharedPtrNode::insertNode(const std::shared_ptr<SharedPtrNode>& value)
{
	if (nullptr == left)
	{
		left = value;
	}
	else if (nullptr == right)
	{
		right = value;
	}
	else
	{
		left->insertNode(value);
	}
}

void SharedPtrNode::binaryInsertNode(const std::shared_ptr<SharedPtrNode>& value)
{
	if (value->data < data)
	{
		if (nullptr == left)
		{
			left = value;
		}
		else
		{
			left->insertNode(value);
		}
	}//so we can handle equal cases
	else 
	{
		if (nullptr == right)
		{
			right = value;
		}
		else
		{
			right->insertNode(value);
		}
	}
}



void SharedPtrNode::printTreeDepthFirst()
{
	std::cout << data;
	if (nullptr != left)
	{
		left->printTreeDepthFirst();
	}
	if (nullptr != right)
	{
		right->printTreeDepthFirst();
	}
}

void SharedPtrNode::printTreeBreadthFirst()
{
	std::queue<SharedPtrNode*> myQueue;
	//Can avoid using this by passing in the node you wish to
	//Start the iteration through a paramter
	myQueue.push(this);


	while (!myQueue.empty())
	{
		SharedPtrNode* node = myQueue.front();;
		myQueue.pop();
		std::cout << node->data;
		if (nullptr != node->left)
		{
			myQueue.push(node->left.get());
		}
		if (nullptr != node->right)
		{
			myQueue.push(node->right.get());
		}
	}
}
