/*
 * Exercise 3.8
 * Author: sesiria  2018
 * set all element of vector to a specified value.
 */
#include <iostream>
#include <vector>

/**
 * set all of the elments from vector to specified value.
 * time complexity O(N) 
 * N is the size of the Vector container.
 */
template <typename Object>
void setVector(std::vector<Object> & v, const Object& val)
{
    for(auto &x : v)
        x = val;
}

int main(int argc, char ** argv)
{
    std::vector<int> pos = {1, 2, 5, 1, 6, 7, 1};

    setVector(pos, 6);
    for(auto &X: pos)
        std::cout << X << " ";
    std::cout << std::endl;
    return 0;
}