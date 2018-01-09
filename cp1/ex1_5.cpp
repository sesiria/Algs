/*
 * Exercise 1.5
 * Author: sesiria  2018
 * Write a recursive function that returns the number 
 * of 0s in the binary representation of N.
 */

#include <iostream>

// get the number of zero in a binary presentation.
int getNumberOfZero(unsigned n)
{
    if(n <= 1)
        return !n;  // inverse to get the number of zero.
    return getNumberOfZero(n / 2) + !(n % 2);
}

int main(int argc, char** argv)
{
    std::cout << "The number of zeros in " << 4 << " is " << getNumberOfZero(4) << std::endl;
    std::cout << "The number of zeros in " << 3 << " is " << getNumberOfZero(3) << std::endl;
    std::cout << "The number of zeros in " << 2 << " is " << getNumberOfZero(2) << std::endl;
    std::cout << "The number of zeros in " << 1 << " is " << getNumberOfZero(1) << std::endl;
    return 0;
}