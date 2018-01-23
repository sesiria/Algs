/*
 * Exercise 3.16
 * Author: sesiria  2018
 * double linklist class. 
 * Inherit from the original version from the textbook.
 * add reverse_iterator and const_reverse_iterator
 * just apply the change to the ../Lib/List.h
 */
#include <iostream>
#include "../Lib/List.h"

template <typename List>
void printList(const List & list)
{
    for(auto &x: list)
        std::cout << x << " ";
    std::cout << std::endl;
}

// print as reverse
template <typename List>
void printListReverse(const List & list)
{
    typename List::const_reverse_iterator iter = list.rbegin();
    while(iter != list.rend())
        std::cout << *iter++ << " ";
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    List<int> list;
    for (int i = 0; i < 10; ++i)
        list.push_back(i*2);
    printList(list);

    printListReverse(list);

    return 0;
}