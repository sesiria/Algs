/*
 * Exercise 3.6
 * Author: sesiria  2018
 * Josephus problem with input N people and M passes.
 */
#include <iostream>
#include <list>

/**
 * Josephus problem solution1
 * n numbers of people
 * m passed.
 * simulate with the linklist
 * time complexity O(N*M)
 * we could optimize for M.
 * add the optimization code will improve the time complexity to O(N*min(N, M))
 */
int solveJosephusProblem1(int n, int m)
{
    std::list<int> list;
    for (int i = 1; i <= n; ++i)
        list.push_back(i);      // build the list for people

    auto iter = list.begin();
    while(list.size() > 1)
    {
        // pass for m times.
        // Optimizization Code. iterations for large M 
        int nIterations = m % list.size();
        for (int i = 0; i < nIterations; ++i, ++iter)
        {
            if(iter == list.end())
                iter = list.begin();    // circular the iter.
        }
        if(iter == list.end())          // if we approach the last element .fix to begin
                iter = list.begin();
        iter = list.erase(iter);        // delete the current people.
        
    }
    if(iter == list.end())              // if we approach the last element .fix to begin
        iter = list.begin();
    return *iter;   // return the last people.
}

int main(int argc, char ** argv)
{
    printf("Solve for Josephus Problem with %d people %d passes, then %d wins!.\n",
         5, 6, solveJosephusProblem1(5, 1));

    printf("Solve for Josephus Problem with %d people %d passes, then %d wins!.\n",
         5, 0, solveJosephusProblem1(5, 0));
    return 0;
}