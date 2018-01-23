/*
 * Exercise 3.9
 * Author: sesiria  2018
 * auto key word and non-member begin/end about iterator.
 */
#include <iostream>
#include <vector>

/**
 * set all of the elments from vector to specified value.
 * time complexity O(N) 
 * N is the size of the Vector container.
 */
template <typename Container>
void printAll(const Container & v)
{
    for (auto iter = begin(v); iter != end(v); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;
}

int main(int argc, char ** argv)
{
    std::vector<int> pos = {1, 2, 5, 1, 6, 7, 1};
    printAll(pos);

    return 0;
}