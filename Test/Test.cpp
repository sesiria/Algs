#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <string>
using namespace std;

// Empty the priority queue and print its contents.
template <typename PriorityQueue>
void dumpContents(const string &msg, PriorityQueue &pq)
{
    cout << msg << ":" << endl;
    while(!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}

// Do some inserts and removes (done in dumpContents).

int main(int argc, char **argv)
{
    priority_queue<int> maxPQ;
    priority_queue <int, vector<int>, greater<int>> minPQ;

    for (int i = 0; i < 10; ++i)
    {
        minPQ.push(i);
        maxPQ.push(i);
    }

    dumpContents("minPQ", minPQ);
    dumpContents("maxPQ", maxPQ);

    return 0;
}