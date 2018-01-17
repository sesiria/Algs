/*
 * Exercise 2.26
 * Author: sesiria  2018
 * compute the majority element.
 * reference instruction manual for data structure and algorithm analysis.
 */
#include <iostream>
#include <vector>

/**
 * find the Majority elements.
 * time complexity O(N)
 */
#define NOT_FOUND   0xffffffff

int findMajorityCandidate(std::vector<int>& v)
{
    int n = v.size();
    if(n == 0)
        return NOT_FOUND;
    else if(n == 1)
        return v[0];  //only one elements.
    else if(n == 2)
    {
        return (v[0] == v[1]) ? v[0] : NOT_FOUND;
    }
    
    // construct the array to found the candidate.
    std::vector<int> b(0);
    for (int i = 1; i < n; i += 2)
    {
        if(v[i] == v[i - 1])
            b.push_back(v[i]);
    }
    int Candidate = findMajorityCandidate(b);
    if(Candidate == NOT_FOUND && n % 2 == 1)
        Candidate = v[n - 1];   // set the last element as candidate.
    return Candidate;
}

// mian function to found the candidate.
int findMajority(std::vector<int> & v)
{
    int Candidate;
    if((Candidate = findMajorityCandidate(v)) == NOT_FOUND)
        return NOT_FOUND;

    int nCount = 0;
    int n = v.size();
    // check whether the candidate is valid.
    for (int i = 0; i < n; ++i)
        if(Candidate == v[i])
        {
            nCount++;
            if(nCount > n/2)
                return Candidate;
        }
    return NOT_FOUND;
}


int main(int argc, char ** argv) 
{
    std::vector<int> v = {3, 3, 4, 2, 4, 4, 2, 4, 4};
    int Candidate = findMajority(v);
    if(Candidate == NOT_FOUND)
        std::cout << "Not Found.!" << std::endl;
    else
        std::cout << Candidate << std::endl;
    return 0;
}