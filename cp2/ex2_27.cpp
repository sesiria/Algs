/*
 * Exercise 2.27
 * Author: sesiria  2018
 * search the element is in and ordered matrix by binary search.
 */
#include <iostream>
#include "../Lib/matrix.h"

inline int isInRange(int low, int high, int val)
{
    if(val < low)
        return -1; // the vale in the previous range.
    if(val > high)
        return 1; // the value is in the next range.

    return 0; // the value is exactly in the range.
}

// a is a N x N square matrix.
// time complexity is O(2logN)
bool searchMatrix(const matrix<int> & a, size_t nSize, int val)
{
    int low = 0, high = nSize - 1;
    // search from matrix range.
    bool bFound = false;
    int mid;
    while(low <= high)
    {
        mid = (high + low) / 2;
        int retValue;
        if((retValue = isInRange(a[mid][0], a[mid][nSize - 1], val)) < 0)
            high = mid - 1;
        else if(retValue > 0)
            low = mid + 1;
        else
        {
            bFound = true;
            break;
        }
    }

    int x = mid;    // restore the x position.
    int y;
    if(bFound)
    {
        bFound = false; // reset bFound.
        int low = 0, high = nSize - 1;
        while(low <= high)
        {
            mid = (low + high) / 2;
            if(a[x][mid] > val)
                high = mid - 1;
            else if (a[x][mid] < val)
                low = mid + 1;
            else
            {
                bFound = true;
                break;
            }
        }
    }

    if(bFound)
    {
        y = mid;
        printf("Found element %d in position [%d, %d].\n", val, x, y);
    }
    return bFound;
}
int main(int argc, char ** argv) 
{
    std::vector<std::vector<int>> vec ={
	    std::vector<int>{1, 3, 5, 7, 9},
	    std::vector<int>{11, 13, 27, 32, 33},
        std::vector<int>{40, 46, 50, 63, 71},
	    std::vector<int>{88, 96, 102, 104, 128},
	    std::vector<int>{196, 256, 384, 512, 1024},
    };
    
    matrix<int> ma = vec;
    searchMatrix(ma, ma.numcols(), 71);
    return 0;
}