/*
 * Exercise 3.7
 * Author: sesiria  2018
 * remove every other item in a list using the erase method.
 */
#include <iostream>
#include <list>

/**
 * remove every other element from the list.
 * time complexity O(N)
 */
template <typename L>
void removeEveryOther(L & list)
{
    for (auto iter = list.begin(); iter != list.end();)
    {
        iter = list.erase(iter);
        if(iter != list.end())  // boundary check.
            ++iter;
    }
}

int main(int argc, char ** argv)
{
    std::list<int> pos = {1, 2, 5, 1, 6, 7, 1};

    removeEveryOther(pos);
    for(auto &X: pos)
        std::cout << X << " ";
    std::cout << std::endl;
    return 0;
}