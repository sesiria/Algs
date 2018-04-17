#include "../Lib/MinMaxHeap.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Test program
int main()
{
    int minItem = 10000; // same number of digits
    int maxItem = 99999;
    MinMaxHeap<string> h;
    string str = "hello";
    int i = 37;
    string x;

    cout << "Begin test... " << endl;

    // test insert and deletemin
    for (i = 37; i != 0; i = (i + 37) % maxItem)
    {
        // should use to_string in C++11
        ostringstream sout;
        sout << "hello" << i;
        if (i >= minItem)
        {
            string s = sout.str();
            h.insert(s);
        }
    }
    for (i = minItem; i < maxItem; ++i)
    {
        ostringstream sout;
        sout << "hello" << i;

        h.deleteMin(x);

        if (x != sout.str())
            cout << "DeleteMin error! " << i << endl;
    }

    // test insert and deletemax
    for (i = 37; i != 0; i = (i + 37) % maxItem)
    {
        // should use to_string in C++11
        ostringstream sout;
        sout << "hello" << i;
        if (i >= minItem)
        {
            string s = sout.str();
            h.insert(s);
        }
    }

    for (i = maxItem - 1; i >= minItem; --i)
    {
        ostringstream sout;
        sout << "hello" << i;

        h.deleteMax(x);

        if (x != sout.str())
            cout << "DeleteMax error! " << i << endl;
    }

    cout << "End test... no other output is good" << endl;
    return 0;
}
