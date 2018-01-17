/*
 * Exercise 2.33
 * Author: sesiria  2018
 * two-way comparison for binary search.
 */
#include <iostream>
#include <vector>

// return the index in the array.
// time complexity O(logN)
template <typename Comparable>
int binarysearch(
    const std::vector<Comparable> & arr, 
    const Comparable &key
    )
{
    int low = 0;
    int high = arr.size() - 1;
    int mid;
    while(low < high) {
        mid = (low + high) / 2;
        if(arr[mid] < key)
            low = mid + 1;
        else
            high = mid; // arr[mid] >= key.
    }
    if(low == high && arr[low] == key)
        return low;
    else
        return -1;
}

int main(int argc, char ** argv) 
{
    std::vector<int> v = {1, 5, 7, 9, 13, 21, 6};
    printf("search for 7 from array. result position %d.\n", binarysearch(v, 7));
    printf("search for 7 from array. result position %d.\n", binarysearch(v, 12));
    return 0;
}