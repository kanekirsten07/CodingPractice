// Callbacks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <functional>

using namespace std;
using namespace std::placeholders;

void foo(std::function<void()> callback )
{
    std::cout << "foo";
    callback();
}

void bar()
{
    std::cout << "bar";
}

int main()
{
    foo(bar);
    return 0;
}
