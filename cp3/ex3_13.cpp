/*
 * Exercise 3.13
 * Author: sesiria  2018
 * double linklist class. 
 * Inherit from the original version from the textbook.
 * add operator --
 * just apply the change to the ../Lib/List.h
 */
#include <iostream>
#include "../Lib/List.h"



int main(int argc, char **argv)
{
    List<int> list;
    for (int i = 0; i < 10; ++i)
        list.push_back(i*2);

    for(auto &X : list)
        std::cout << X << " ";
    std::cout << std::endl;
    return 0;
}