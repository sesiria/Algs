/*
 * Exercise 3.1
 * Author: sesiria  2018
 * print the element of an list by the specified position.
 */

#include <iostream>
#include <vector>
#include <list>

/**
 * print the element from the specified positon. Vector or Linklist
 * list contains the elements
 * p contains the specified position.
 * time complexity is O(N)
 */ 
template <typename L>
void printLots(const L& list, const std::vector<int>& p)
{
    size_t pos = 0;
    auto iterL = begin(list);
    auto iterP = begin(p);
    for (; iterL != end(list) && iterP != end(p); iterL++, pos++)
    {
        if(pos == *iterP)                   // we have iterate to the specified positon
        {
            std::cout << *iterL << " ";     // print out the elements.
            ++iterP;                        // iterate to the next position.
        }
    }
}

int main(int argc, char ** argv)
{
    std::vector<int> pos = {1, 2, 5, 6, 7};
    std::vector<int> list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<char> linklist = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    printLots(list, pos);
    std::cout << std::endl;
    printLots(linklist, pos);
    return 0;
}