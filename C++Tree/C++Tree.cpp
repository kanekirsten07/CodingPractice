// C++Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Node.h"
#include "SharedPtrNode.h"
#include "KirstenSharedPtr.h"
#include <vector>

void testScope1(KirstenSharedPtr& copy1)
{
    KirstenSharedPtr copy = copy1;
    if (copy.GetRefCounter() == copy1.GetRefCounter())
    {
        std::cout << "Scope Ref counter is correct" << std::endl;
    }
    else
    {
        std::cout << "Scope Ref Counter is wrong" << std::endl;
    }
}

void testScope2(KirstenSharedPtr copy2)
{
    if (copy2.GetRefCounter() == 2)
    {
        std::cout << "Scope Ref2 counter is correct" << std::endl;
    }
    else
    {
        std::cout << "Scope Ref2 Counter is wrong" << std::endl;
    }
}


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

    KirstenSharedPtr kirstenSharedPtr = KirstenSharedPtr(7);
    KirstenSharedPtr kirstenSharedPtr2 = KirstenSharedPtr(kirstenSharedPtr);

    if (kirstenSharedPtr == kirstenSharedPtr2)
    {
        std::cout << "great success!" << std::endl;
    }
    else
    {
        std::cout << "something is wrong" << std::endl;
    }

    auto kirstenSharedPtr3 = kirstenSharedPtr2;
    if (kirstenSharedPtr3 == kirstenSharedPtr2)
    {
        std::cout << "assignment constructor success" << std::endl;
    }
    else
    {
        std::cout << "assignment constructor fail" << std::endl;
    }

    KirstenSharedPtr sharedPtr = KirstenSharedPtr(1);
    if (sharedPtr.GetRefCounter() == 1)
    {
        std::cout << "Ref counter is correct" << std::endl;
    }
    else
    {
        std::cout << "Ref Counter is wrong" << std::endl;
    }

    testScope1(sharedPtr);
    testScope2(sharedPtr);
    if (sharedPtr.GetRefCounter() == 1)
    {
        std::cout << "Ref counter post scope is correct" << std::endl;
    }
    else
    {
        std::cout << "Ref Counter post scope is wrong" << std::endl;
    }

    std::vector<KirstenSharedPtr> myVector;
    KirstenSharedPtr sharedPtr2 = KirstenSharedPtr(2);
    myVector.push_back(sharedPtr2);
    myVector.push_back(sharedPtr2);
    myVector.push_back(sharedPtr2);
    myVector.push_back(sharedPtr2);
    if (myVector.size() == sharedPtr2.GetRefCounter()-1)
    {
        //This will be off by one because of the copy constructor of push_back
        std::cout << "Ref Counter vector is correct" << std::endl;
    }
    else
    {
        std::cout << "Ref counter vector is wrong" << std::endl;
    }

    return 0;
}