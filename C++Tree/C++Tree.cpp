// C++Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Node.h"
#include "SharedPtrNode.h"
//Why do i need to include the .cpp and not the header
#include "KirstenSharedPtr.cpp"


int main()
{
    std::cout << "Hello World! Here is my tree!\n";
    /* Example 1*/
    Node* n = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);

    n->insertNode(n2);
    n->insertNode(n3);

    n->printTree();
    delete n;
    delete n2;
    delete n3;

    /* Example 2*/
    std::cout << "Hello World! Here is my tree with shared pointers!!\n";
    auto sharedPtrNode = std::make_shared<SharedPtrNode>(1);
    auto sharedPtrNode2 = std::make_shared<SharedPtrNode>(2);
    auto sharedPtrNode3 = std::make_shared<SharedPtrNode>(3);
    auto sharedPtrNode4 = std::make_shared<SharedPtrNode>(4);
    auto sharedPtrNode5 = std::make_shared<SharedPtrNode>(5);

    sharedPtrNode->insertNode(sharedPtrNode2);
    sharedPtrNode->insertNode(sharedPtrNode3);
    sharedPtrNode->insertNode(sharedPtrNode4);
    sharedPtrNode->insertNode(sharedPtrNode5);

    std::cout << "Depth First" << std::endl;
    sharedPtrNode->printTreeDepthFirst();
    std::cout << "Breadth first" << std::endl;
    sharedPtrNode->printTreeBreadthFirst();

    auto binarysharedPtrNode = std::make_shared<SharedPtrNode>(3);
    auto binarysharedPtrNode2 = std::make_shared<SharedPtrNode>(1);
    auto binarysharedPtrNode3 = std::make_shared<SharedPtrNode>(2);
    auto binarysharedPtrNode4 = std::make_shared<SharedPtrNode>(4);
    auto binarysharedPtrNode5 = std::make_shared<SharedPtrNode>(5);

    binarysharedPtrNode->binaryInsertNode(sharedPtrNode2);
    binarysharedPtrNode->binaryInsertNode(sharedPtrNode3);
    binarysharedPtrNode->binaryInsertNode(sharedPtrNode4);
    binarysharedPtrNode->binaryInsertNode(sharedPtrNode5);

    std::cout << "binary bredepthadth first" << std::endl;
    binarysharedPtrNode->printTreeDepthFirst();
    std::cout << "binary breadth first" << std::endl;
    binarysharedPtrNode->printTreeBreadthFirst();

    std::cout << "Custom Shared Ptr Implementation" << std::endl;

    auto kirstenSharedPtr = KirstenSharedPtr::Make(7);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
