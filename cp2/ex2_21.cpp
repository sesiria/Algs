/*
 * Exercise 2.21
 * Author: sesiria  2018
 * Sieve of Eratosthenes method to compute all primes less than N.
 * https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 */
#include <iostream>
#include <vector>
#include <math.h>
#include <assert.h>


/**
 * determine the prime number
 * complexity O(sqrt(N))
 */
bool isPrime(int n)
{
    if(n < 2)
        return false;
    else if(n == 2)
        return true;

    int root = (int)sqrt(n);
    for (int i = 2; i <= root; ++i)
    {
        if( n % i == 0)
            return false;
    }
    return true;
}


/**
 * Siev of Eratosthenes algorithm
 * time complexity O(NloglogN)
 * the deduction is used the Merten's second theorem.
 */
std::vector<int> findPrime(int n)
{
    assert(n >= 2);
    std::vector<bool> vecPrime(n+1, true);
    std::vector<int> prime(0);
    int root = (int)sqrt(n);
    for (int i = 2; i < root; i++)
    {
        if(isPrime(i)){
            for (int j = 2 * i; j < n; j += i)
                vecPrime[j] = false;
        }
    }

    for (int k = 2; k < n; ++k)
        if(vecPrime[k])
            prime.push_back(k);

    return prime;
}

int main(int argc, char ** argv) 
{
    std::vector<int> primes = findPrime(100);
    for (int i = 0; i < primes.size(); ++i)
    {
        if(i > 0 && i % 5 == 0)
            std::cout << std::endl;
        std::cout << primes[i] << "\t";
    }
    return 0;
}