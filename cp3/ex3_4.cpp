/*
 * Exercise 3.4
 * Author: sesiria  2018
 * Write a code typically used to print the items in a vector v
 * prior to the introduction of range-based for loops in C++1
 */
#include <iostream>
#include <vector>

/**
 * range-based printout of element of a vector
 * time complexity O(N)
 */
template <typename Object>
void printItems(const std::vector<Object> & v)
{
    for(auto &x : v)
        std::cout << x << " ";
    std::cout << std::endl;
}

int main(int argc, char ** argv)
{
    std::vector<int> pos = {1, 2, 5, 1, 6, 7, 1};

    printItems(pos);
    return 0;
}