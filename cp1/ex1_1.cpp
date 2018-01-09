/*
 * Exercise 1.1
 * Author: sesiria  2018
 * Write a program to solve the selction problem. 
 * Let k = N/2
 */
#include <iostream>
#include <vector>
#include <assert.h>


template <typename Comparable>  
void bubblesort(std::vector<Comparable>& arr) {  
    for (int i = 0; i < arr.size(); i++) {  
        for(int j = 0; j < arr.size() - i - 1; j++) {  
            if(arr[j] > arr[j + 1])  
                std::swap(arr[j], arr[j + 1]) ;
        }  
    }  
}  
  
// Select the k-th largest number from a array.  
template <typename Comparable>
const Comparable & kselection(std::vector<Comparable>& arr, int k) {  
    assert(k <= arr.size() && k > 0);
    bubblesort(arr);  
    return arr[arr.size() - k];  
}  

int main(int argc, char ** argv)
{
    int N = 0;
    std::cout << "Please input the size of the array:";
    std::cin >> N;
    assert(N > 0);
    std::vector<int> array(N);
    for( auto & x : array)
        std::cin >> x;
    std::cout << "The N/2 of k-selection is:" << 
        kselection(array, N/2) << std::endl;
    return 0;
}