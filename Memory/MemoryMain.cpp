#include <iostream>
#include <cstddef>

int main()
{
    std::byte b{42};
    std::cout << std::to_integer<int>(b) << std::endl;
    return 0;
}