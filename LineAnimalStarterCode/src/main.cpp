#include <iostream>
#include <vector>
#include "Engine/Debug.hpp"
#include "App.hpp"


int main(int argc, char *argv[])
{
    App app;
    app.Run();

    unsigned int a = 5u, b = 7u;
    // a (00000101), b (00000111)

    std::cout << "a & b = " << (a & b) << std::endl; // (00000101)

    std::cout << "a | b = " << (a | b) << std::endl; // (00000111)

    std::cout << "a ^ b = " << (a ^ b) << std::endl; // (00000010)

    std::cout << "~a = " << (~a) << std::endl; // (11111010)

    std::cout << "a << 1 = " << (a << 1) << std::endl;

    std::cout << "a >> 1 = " << (a >> 1) << std::endl;

    std::cout << "Hello World" << std::endl;

    return 0;
}