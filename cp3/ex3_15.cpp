/*
 * Exercise 3.15
 * Author: sesiria  2018
 * double linklist class. 
 * Inherit from the original version from the textbook.
 * add operator splice method for List
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

int main(int argc, char **argv)
{
    List<int> list;
    for (int i = 0; i < 10; ++i)
        list.push_back(i*2);
    printList(list);

    List<int> list1;
    for (int i = 0; i < 10; ++i)
        list1.push_back(i);
    printList(list1);

    list.splice((list.begin() + 5), list1);
    printList(list);
    printList(list1);

    
    return 0;
}