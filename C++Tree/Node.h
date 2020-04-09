#pragma once
class Node
{
public:
	int data;
	Node* left;
	Node* right;
	Node(int d)
	{
		data = d;
		left = nullptr;
		right = nullptr;
	}
	Node* insertNode(Node* root, int value);
	void printTree(Node* n);
};

