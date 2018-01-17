/*
 * Exercise 2.20
 * Author: sesiria  2018
 * a) determine prime number.
 * b) the complexity of a) is O(sqrt(N))
 * c) let B equal the number of bits in the inbary representation of N.
 *   what is the value of B?
 * d) the worst-case time is O(sqrt(2^B))
 * e) max input for 20bit is A = 2^20  max input for 40bit is B = 2^40
 *   thus A^2 = B. so Ta^2 = Tb
 * f) B is better measure because it 
 * more accurately represents the size of the input
 */
#include <iostream>
#include <vector>
#include <math.h>


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
 * return the number of bits of input number n.
 */
int getBits(long long n)
{
    int nBits = 0;
    while( n != 0)
    {
        nBits++;
        n /= 2;
    }
    return nBits;
}

int main(int argc, char ** argv) 
{
    if(isPrime(3455517))
        std::cout << "7 is prime." << std::endl;

    std::cout << getBits(0) << std::endl;
    return 0;
}