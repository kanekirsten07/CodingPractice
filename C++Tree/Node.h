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
	void insertNode(Node* value);
	void printTree();
};

