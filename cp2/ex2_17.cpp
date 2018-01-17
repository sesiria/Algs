/*
 * Exercise 2.17
 * Author: sesiria  2018
 * a) Find the minimum subsequence sum.
 * b) Find the minimum positive subsequence sum.
 * c) Find the maximum subsequence product.
 * The detail about the analysis refere the link
 * https://www.cnblogs.com/clairvoyant/p/4944737.html
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

/**
 * find the minimum subsequence sum.
 * assume that the vector include postive and negative integers.
 */
int minSubSum(const std::vector<int> & a)
{
    int minSum = 0, thisSum = 0;
    for (int j = 0; j < a.size(); ++j)
    {
        thisSum += a[j];
        
        if(thisSum < minSum)
            minSum = thisSum;
        else if(thisSum > 0)
            thisSum = 0;
    }
    return minSum;
}


/**
 * find the minimum postive subsequence sum.
 * assume that the vector include postive and negative integers.
 * O(N^2)
 */
int minSubPositiveSum1(const std::vector<int> & a)
{
    int minSum = 0, thisSum = 0;
    // init minSum.
    for (int i = 0; i < a.size(); ++i)
    {
        if(minSum == 0 && a[i] > 0)
            minSum = a[i];
        if(a[i] < minSum && a[i] > 0)
            minSum = a[i];
    }    

    for (int i = 0; i < a.size(); ++i)
    {
        thisSum = 0;
        for (int j = i; j < a.size(); ++j)
        {
            thisSum += a[j];
            if(minSum > thisSum && thisSum > 0)
                minSum = thisSum;
        }
    }
    return minSum;
}


typedef struct{
    int value;
    int index;
    bool isEqual;
} Node;

bool compare(const Node& p1, const Node& p2)
{
    if(p1.value == p2.value)
        return p1.index > p2.index;
    else
        return p1.value < p2.value;
}

/**
 * find the minimum postive subsequence sum.
 * assume that the vector include postive and negative integers.
 * Improvement. time complexity. O(N)
 */
int minSubPositiveSum2(const std::vector<int> & a)
{
    std::vector<Node> vec(a.size());
    int subsum = 0;
    // build the prefix subarray.
    for (int i = 0; i < a.size(); ++i)
    {
        subsum += a[i];
        vec[i].value = subsum;
        vec[i].index = i;
        vec[i].isEqual = false;
    }

    // standard qsort O(NlogN).
    // if the vec is not a distinct element array it has some bugs.
    // try to swap some element to fix the bugs.
    // we just modify the compare function to fix this bugs.
    // for input {-10, 22, -1} it still has some bugs.
    std::sort(vec.begin(), vec.end(), compare); 

    int minSum = vec[0].value > 0 ? vec[0].value : 2<<29;
    int thisSum = 0;
    for (int j = 1; j < vec.size(); ++j)   
    {
        // if vec[j].value == vec[j-1].value the algorithm will have some bugs.
        // try to swap the two element.
        /*if(vec[j].value == vec[j-1].value && vec[j].index > vec[j-1].index)
            std::swap(vec[j], vec[j - 1]);*/
        if(vec[j].index > vec[j-1].index) // the high index contain the low index subarray.
        {
            thisSum = vec[j].value - vec[j - 1].value;
            if(thisSum > 0 && thisSum < minSum)
                minSum = thisSum;
        }
    }
	return minSum;
}

/**
 * find the maximum subsequence product.
 * assume that the vector include postive and negative integers.
 * Use the dynamic program method. Complexity O(N)
 */
int maxSubProduct(const std::vector<int> & a)
{
	int maxProduct = 0, minProduct = 0, max = 0;

	for (int j = 0; j < a.size(); ++j)
	{
        int tempMax = maxProduct;
        int tempMin = minProduct;
        // update max and min simultaneously.
        maxProduct = std::max(a[j], std::max(a[j] * tempMax, a[j] * tempMin));
        minProduct = std::min(a[j], std::min(a[j] * tempMax, a[j] * tempMin));
        if(std::max(maxProduct, minProduct) > max)
            max = std::max(maxProduct, minProduct);
    }

	return max;
}

int main(int argc, char ** argv) 
{
    std::vector<int> v = {-10, 22, -1}; //{23, -11, 3, -3, -1, 1, -1, 14}; /*{-2,11,-4,13,-5,-2};*/ //{11,  12,  -11,  10,  -5,  -6,  19};
    std::cout << minSubPositiveSum2(v) << std::endl;
    return 0;
}