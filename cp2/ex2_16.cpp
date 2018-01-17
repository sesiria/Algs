/*
 * Exercise 2.16
 * Author: sesiria  2018
 * Different implementation of GCD algorithm.
 */
#include <iostream>
#include <vector>

int gcd(int a, int b)
{
    if(a < b)
        std::swap(a, b);
    if(b == 0)
        return a;
    int amod = a % 2;
    int bmod = b % 2;
    if(amod == 0 && bmod == 0)
        return 2 * gcd(a / 2, b / 2);
    else if(amod == 0 && bmod == 1)
        return gcd(a / 2, b);
    else if(amod == 1 && bmod == 0)
        return gcd(a, b / 2);
    else
        return gcd((a + b) / 2, (a - b) / 2);
}


int main(int argc, char ** argv) 
{
    printf("the gcd of %d and %d is %d.\n", 391, 207, gcd(391, 207));
    return 0;
}