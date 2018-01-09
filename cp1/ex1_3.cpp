/*
 * Exercise 1.3
 * Author: sesiria  2018
 * Write a recursive routine to print for a non-negative integer n
 * to print our digits. For exp, for n = 76543
 */

#include <iostream>
#define printdigit(a)   \
    {                   \
        std::cout << a; \
    }

// recursive routine to print out non-negative digit.
void printOut(unsigned n)
{
    if(n >= 10)
        printOut(n / 10);
    printdigit(n % 10);
}

int main(int argc, char ** argv)
{
    // test case.
    printOut(7236);
    std::cout << std::endl;
    printOut(4);
    std::cout << std::endl;
    printOut(0);
    std::cout << std::endl;
    return 0;
}