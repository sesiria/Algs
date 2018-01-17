/*
 * Exercise 2.7
 * Author: sesiria  2018
 * Compare the complexity of six algorithm.
 */

#include <iostream>
#include <time.h>
#include <vector>

// algorithm1 time complexity O(N)
int calcSum1(int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i)
        ++sum;
    return sum;
}

// algorithm2 time complexity O(N^2)
int calcSum2(int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            ++sum;
    return sum;
}

// algorithm3 time complexity O(N^3)
int calcSum3(int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n * n; ++j)
            ++sum;
    return sum;
}

// algorithm4 time complexity O(N^2)
int calcSum4(int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            ++sum;
    return sum;
}

// algorithm5 time complexity O(N^5)
int calcSum5(int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i * i; ++j)
            for (int k = 0; k < j; ++k)
                ++sum;
    return sum;
}

// algorithm6 time complexity O(N^5)
int calcSum6(int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i * i; ++j)
            if(j % i == 0)
                for (int k = 0; k < j; ++k)
                    ++sum;
    return sum;
}

// test data.
typedef int (*CALCFUN)(int N);
std::vector<CALCFUN> g_func = {calcSum1, calcSum2, calcSum3, calcSum4, calcSum5, calcSum6};
std::vector<std::string> g_str = {"O(N)", "O(N^2)", "O(N^3)", "O(N^2)", "O(N^5)", "O(N^4)"};

void testAlgorithms(int nSample)
{
    printf("Start to test %d algorithms with sample number %d.\n", g_func.size(), nSample);
    for (int i = 0; i < g_func.size(); i++)
    {
        printf("Start to test algorithm %d with theory complexity %s\n", i+1, g_str[i].c_str());
        clock_t nStart = clock();
        g_func[i](nSample);
        clock_t nEnd = clock();
        printf("Time elapsed %f\n", (nEnd - nStart) / (float)CLOCKS_PER_SEC);
    }
}

int main(int argc, char ** argv)
{
    testAlgorithms(10);
    testAlgorithms(100);
    testAlgorithms(200);
    return 0;
}