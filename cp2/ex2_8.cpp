/*
 * Exercise 2.8
 * Author: sesiria  2018
 * large Random number generator.
 * algorithm to do the permutation.
 */
#include <iostream>
#include <vector>
#include <time.h>
#include "../Lib/randomize.h"

// fill the array a from a[0] to a[n-1] with different number.
// search every time.
// algorithm time complexity O(N^3)
std::vector<int> createRandArray1(int n)
{
    std::vector<int> a(n, 0);  // create an array with size n.
    for (int i = 0; i < n; ++i)
    {
        int k;
        bool bFound;
        do {
            bFound = false;
            // generate an random number from 1~ N.
            k = randInt(1, n);      
            for (int j = 0; j <= i; ++j)
                if(a[j] == k)
                    bFound = true;
        } while (bFound);

        // store the generated random number.
        a[i] = k; 
    }
    return a;
}

// fill the array a from a[0] to a[n-1] with different number.
// keep an hash table.
// algorithm time complexity O(N~N^2)
std::vector<int> createRandArray2(int n)
{
    std::vector<int> a(n, 0);            // create an array with size n.
    std::vector<bool> hash(n, false);    // create an hash table for further reference.
    for (int i = 0; i < n; ++i)
    {
        int k;
        do {   
            k = randInt(1, n);           // generate an random number from 1~ N.    
        } while (hash[k - 1]);

        a[i] = k;                        // store the generated random number.
        hash[k - 1] = true;              // mark the hash table.
    }
    return a;
}

// fill the array a from a[0] to a[n-1] with different number.
// use shuffle algorithm.
// algorithm time complexity O(N)
std::vector<int> createRandArray3(int n)
{
    std::vector<int> a(n);            // create an array with size n.
    for (int i = 0; i < n; ++i)
    {
        a[i] = i + 1;
    }
    for (int i = 0; i < n; ++i)
    {
        std::swap(a[i], a[randInt(0, i)]);
    }    
    return a;
}


// test data.
typedef std::vector<int> (*CALCFUN)(int N);
std::vector<CALCFUN> g_func = {createRandArray1, createRandArray2, createRandArray3};
std::vector<std::string> g_str = { "O(N^3)", "O(N~N^2)", "O(N)" };

// test engine.
void testAlgorithms(int nSample)
{
    printf("Start to %d algorithms with sample number %d.\n", g_func.size(), nSample);
    for (int i = 0; i < g_func.size(); i++)
    {
        printf("Start to test algorithm %d with theory complexity %s\n", i+1, g_str[i].c_str());
        clock_t nStart = clock();
        g_func[i](nSample);
        clock_t nEnd = clock();
        printf("Time elapsed %f\n", (nEnd - nStart) / (float)CLOCKS_PER_SEC);
    }
}

// id the algorithm id.
// nSample the input sample space.
// repetition times for loops.
void testIterations(int id, int nSample, int repetition)
{
    printf("Start to test algorithms %d with sample number %d. for %d times\n", id + 1, nSample, repetition);
    printf("Algorithm %d with theory complexity %s\n", id+1, g_str[id].c_str());
    clock_t totalTime = 0;
    for (int i = 0; i < repetition; i++)
    {    
        clock_t nStart = clock();
        g_func[id](nSample);
        clock_t nEnd = clock();
        totalTime += (nEnd - nStart);
    }
    printf("Average time elapsed %f\n", totalTime / (float)(CLOCKS_PER_SEC * repetition));
}

// test for algorithm1.
void testCase1()
{
    std::vector<int> v = {250, 500, 1000, 2000}; // sample space.
    for (int i = 0; i < v.size(); ++i)
        testIterations(0, v[i], 10);
}

// test for algorithm2.
void testCase2()
{
    std::vector<int> v = {25000, 50000, 100000, 200000, 400000, 800000}; // sample space.
    for (int i = 0; i < v.size(); ++i)
        testIterations(1, v[i], 10);
}

// test for algorithm3.
void testCase3()
{
    std::vector<int> v = {100000, 200000, 400000, 800000, 1600000, 3200000, 6400000}; // sample space.
    for (int i = 0; i < v.size(); ++i)
        testIterations(2, v[i], 10);
}

int main(int argc, char ** argv)
{
    testCase1();
    testCase2();
    testCase3();
    return 0;
}