/*
 * Exercise 1.6
 * Author: sesiria  2018
 * Print permutations of a string.
 */
#include <iostream>
#include <string>

void permute(std::string &str);
void permute(std::string &str, int low, int high);

void permute(std::string &str, int low, int high)
{
    if(low == high) // we reach the last element.
    {
        std::cout << str << std::endl;  // print the string.
        return;
    }

    for (int i = low; i <= high; ++i)
    {
        std::swap(str[i], str[low]);  //swap the element temporary.
        permute(str, low + 1, high);
        std::swap(str[i], str[low]); // recover the element.
    }
}

void permute(std::string &str)
{
    permute(str, 0, str.size() - 1);
}

int main(int argc, char ** argv)
{
    std::string str = "ABCD";
    permute(str);
    return 0;
}