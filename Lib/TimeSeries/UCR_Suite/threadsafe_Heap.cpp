// unit test function for thread_safe heap.
#include "threadsafe_Heap.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <functional>

using namespace std;

using threadsafe_Heap = threadsafe_priority_queue<int, vector<int>, std::greater<int>>;

void worker(threadsafe_Heap & Heap, int param)
{
    Heap.push(param);

    for (int i = 0; i < 1000; ++i) {
        Heap.push_and_pop(i * param);
    }
}

int main()
{
    threadsafe_Heap Heap;
    std::vector<std::thread> threads;
    for (int  i = 0; i < 10; ++i) {
        threads.push_back(std::thread(worker, std::ref(Heap), i));
    }

    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));


    Heap.push(1);
    Heap.push_and_pop(2);
    while (!Heap.empty())
    {
        cout << Heap.top() << endl;
        Heap.try_pop();
    }

    return 0;
}