/*
 * Exercise 3.14
 * Author: sesiria  2018
 * double linklist class. 
 * Inherit from the original version from the textbook.
 * add operator + for advance some steps.
 * just apply the change to the ../Lib/List.h
 */
#include <iostream>
#include "../Lib/List.h"



int main(int argc, char **argv)
{
    List<int> list;
    for (int i = 0; i < 10; ++i)
        list.push_back(i*2);

    auto iter = list.begin();
    std::cout << *(iter + 5) << std::endl;
    *(iter + 5) = 11;
    std::cout << *(iter + 5) << std::endl;
    std::cout << std::endl;
    return 0;
}