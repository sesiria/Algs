/*
 * Exercise 2.19
 * Author: sesiria  2018
 * return the actual max sub sequence of from an array.
 */
#include <iostream>
#include <vector>


/**
 * find the maximum subsequence.
 * return the sum and the indice of the actual sequence.
 * assume that the vector include postive and negative integers.
 * Use the dynamic program method. Complexity O(N)
 */
std::vector<int> maxSubSequence(const std::vector<int> & a, int & maxSum)
{
    int thisSum = 0;
    int maxStart = 0, maxEnd = 0;
    int tmpStart = 0;
    std::vector<int> maxSubSeq(0);

    maxSum = 0;
    for (int j = 0; j < a.size(); ++j)
	{
        if(thisSum == 0)
            tmpStart = j; // record the start position.

        thisSum += a[j];
        if(thisSum > maxSum)
        {
            maxStart = tmpStart; // record the max startPos.
            maxEnd = j;
            maxSum = thisSum;
        }
        else if (thisSum < 0)
        {
            thisSum = 0;
        }
    }

    for (int i = maxStart; i <= maxEnd; ++i)
        maxSubSeq.push_back(a[i]);
    return maxSubSeq;
}

int main(int argc, char ** argv) 
{
    std::vector<int> v = {11,  12,  -11,  10,  -5,  -6,  19};
    int maxSum = 0;
    std::vector<int> maxSeq = maxSubSequence(v, maxSum);
    std::cout << "The max sub sequence elements is:" << std::endl;
    for(auto A : maxSeq)
        std::cout << A << " ";
    return 0;
}