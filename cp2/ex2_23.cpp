/*
 * Exercise 2.23
 * Author: sesiria  2018
 * calculate power without recursion.
 */
#include <iostream>

/**
 * Calculate the power of x^n without recurssion.
 * time complexity O(logN)
 */
long long pow(long long x, int n)
{
    long long power = 1;
    while(n != 0)
    {
        if(n % 2 == 0)
        {
            x = (x * x);
            n /= 2;
        }        
        else
        {
            power *= x;
            --n;
        }
    }
    return power;
}


int main(int argc, char ** argv) 
{
    std::cout << pow(2, 0) << std::endl;
    std::cout << pow(2, 1) << std::endl;
    std::cout << pow(2, 2) << std::endl;
    std::cout << pow(2, 3) << std::endl;
    std::cout << pow(2, 7) << std::endl;
    std::cout << pow(2, 16) << std::endl;
    return 0;
}