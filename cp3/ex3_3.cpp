/*
 * Exercise 3.3
 * Author: sesiria  2018
 * Implementation for STL count rountine.
 */
#include <iostream>
#include <vector>

/**
 * return the count of occurences of x in the range from start 
 * and extends up to but not incuding end.
 * time complexity O(N)
 */
template <typename Iterator, typename Object>
int count(Iterator start, Iterator end, const Object &x) 
{
    int nCount = 0;
    for (auto iter = start; iter != end; ++iter)
    {
        if(*iter == x)
            nCount++;
    }
    return nCount;
}

int main(int argc, char ** argv)
{
    std::vector<int> pos = {1, 2, 5, 1, 6, 7, 1};

    std::cout << count(begin(pos), end(pos), 1) << std::endl;
    std::cout << count(begin(pos), end(pos), 0) << std::endl;
    return 0;
}