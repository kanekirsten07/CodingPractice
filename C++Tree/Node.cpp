#include "Node.h"
#include <iostream>
Node* Node::insertNode(Node* root, int value)
{
	if (nullptr == root)
	{
		root = new Node(value);
		return root;
	}
	else if (nullptr == root->left)
	{
		root->left= insertNode(root->left, value);
	}
	else
	{
		root->right = insertNode(root->right, value);
	}
}

void Node::printTree(Node* n)
{
	if (nullptr == n)
		return;

	std::cout << n->data;
	printTree(n->left);
	printTree(n->right);
}