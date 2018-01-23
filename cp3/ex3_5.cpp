/*
 * Exercise 3.5
 * Author: sesiria  2018
 * Write a code typically used to print the items in a vector v
 * base on the begin and end methods with checking for "out-of-bounds"
 */
#include <iostream>
#include <vector>

/**
 * iteration-based print elements of vector
 * time complexity O(N)
 */
template <typename Object>
void printItems(const std::vector<Object> & v)
{
    for (auto iter = v.begin(); iter != v.end(); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;
}

int main(int argc, char ** argv)
{
    std::vector<int> pos = {1, 2, 5, 1, 6, 7, 1};

    printItems(pos);
    return 0;
}