/*
 * Exercise 2.15
 * Author: sesiria  2018
 * Determine whether a sorted array exist an integer i such that
 * Ai = i.
 */
#include <iostream>
#include <vector>


int findI(const std::vector<int> &a)
{
    int low = 1, high = a.size() - 1;
    while(low <= high)
    {
        int mid = (low + high) / 2;
        if(a[mid] < mid)
            low = mid + 1;
        else if(a[mid] > mid)
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}


int main(int argc, char ** argv) 
{
    std::vector<int> array = {0, -10, 1, 2, 3, 5, 7, 9, 10};
    std::cout << findI(array) << std::endl;
    return 0;
}