/*
 * Exercise 2.28
 * Author: sesiria  2018
 * calculate combination of max value from an array.
 */
#include <iostream>
#include <vector>
#include <algorithm>


/**
 * get the max sum of two element from a postive integer array.
 * find the largest number in the array.
 * complexity O(N)
 */
int maxSumOfTwoElement(const std::vector<int>& a)
{
    int maxidx1 = 0, maxidx2 = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        if(a[i] > a[maxidx1])
        {
            maxidx2 = maxidx1;
            maxidx1 = i;
        } else if(a[i] > a[maxidx2])
        {
            maxidx2 = i;
        }
    }
    if(maxidx1 < maxidx2)
        std::swap(maxidx1, maxidx2);
    int sum = a[maxidx1] + a[maxidx2];
    printf("max sum is a[%d] + a[%d] = %d.\n", maxidx1, maxidx2, sum);
    return sum;
}

/**
 * get the max diference of two element from a postive integer array.
 */
int maxDiferenceOfTwoElement(const std::vector<int>& a)
{
    int maxid = 0, minid = 0;
    int tempMinID = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        if(a[i] > a[maxid])
        {
            maxid = i;
            minid = tempMinID; // update the previous tempMinID;
        }
        else if (a[i] < a[minid])
        {
            tempMinID = i; // record the minID temporaryly.
        }
    }

    int difference = a[maxid] - a[minid];
    printf("max difference is a[%d] - a[%d] = %d.\n", maxid, minid, difference);
    return difference;
}

/**
 * get the max product of two element from a postive integer array.
 * complexity O(N)
 */
int maxProductOfTwoElement(const std::vector<int>& a)
{
    int maxidx1 = 0, maxidx2 = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        if(a[i] > a[maxidx1])
        {
            maxidx2 = maxidx1;
            maxidx1 = i;
        } else if(a[i] > a[maxidx2])
        {
            maxidx2 = i;
        }
    }
    if(maxidx1 < maxidx2)
        std::swap(maxidx1, maxidx2);
    int product = a[maxidx1] * a[maxidx2];
    printf("max product is a[%d] * a[%d] = %d.\n", maxidx1, maxidx2, product);
    return product;
}

/**
 * get the max quotient of two element from a postive integer array.
 */
int maxQuotientOfTwoElement(const std::vector<int>& a)
{
    int maxid = 0, minid = 0;
    int tempMinID = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        if(a[i] > a[maxid])
        {
            maxid = i;
            minid = tempMinID; // update the previous tempMinID;
        }
        else if (a[i] < a[minid])
        {
            tempMinID = i; // record the minID temporaryly.
        }
    }

    int quotient = a[maxid] / a[minid];
    printf("max quotient is a[%d] / a[%d] = %d.\n", maxid, minid, quotient);
    return quotient;
}

int main(int argc, char ** argv) 
{
    std::vector<int> v = {11, 5, 12, 3, 7, 9, 16, 28, 4};
    maxSumOfTwoElement(v);
    maxProductOfTwoElement(v);
    maxDiferenceOfTwoElement(v);
    maxQuotientOfTwoElement(v);
    return 0;
}