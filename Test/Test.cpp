#include <iostream>
#include <vector>
#include <time.h>


int findI(const std::vector<int> &a)
{
    int low = 1, high = a.size() - 1;
    while(low <= high)
    {
        int mid = (low + high) / 2;
        if(a[mid] < mid)


    }
    return -1;
}


int main(int argc, char ** argv) 
{
    std::vector<int> array = {0, -1, 0, 2, 3, 5, 7, 9, 10};
    return 0;
}