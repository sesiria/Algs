/**
 * Exercise 6.18
 * Author: sesiria  2018
 * min-max heap implementation support the following interface
 * 1) insert for O(logN)
 * 2) deleteMin for O(logN)
 * 3) deleteMax for O(logN)
 * 4) buildheap for O(N)
 */
#include "../Lib/MinMaxHeap.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main()
{
	MinMaxHeap<int> h;
	int maxItem = 20;
	int step = 3;
    int ncount;
    for (int i = step; i != 0; i = (i + step) % maxItem)
	{
		// should use to_string in C++11
		h.insert(i);
	}

    ncount = 0;
    for (int i = step; i != 0; i = (i + step) % maxItem)
	{
		int x = 0;
		h.deleteMax(x);
        if(ncount++ % 10 == 0)
            cout << endl;
        cout << x << " ";
	}

	for (int i = step; i != 0; i = (i + step) % maxItem)
	{
		// should use to_string in C++11
		h.insert(i);
	}
	cout << endl;
    ncount = 0;
	for (int i = step; i != 0; i = (i + step) % maxItem)
	{
		int x = 0;
		h.deleteMin(x);
        if(ncount++ % 10 == 0)
            cout << endl;
		cout << x << " ";
	}
    return 0;
}