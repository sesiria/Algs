/*
 * Exercise 3.28
 * Author: sesiria  2018
 * Deque support push pop and findMin 
 * Deque implentaton support the following routine:
 * push, pop, inject, eject take time per operation O(1)
 */
#include <iostream>
#include "../Lib/List.h"

template <typename Object>
class Deque
{
  public:
    // default constructor.
    Deque() = default;
    // destructor
    ~Deque() = default;
    // copy constructor
    Deque(const Deque &rhs) = default;
    // copy assignment operator
    Deque &operator=(const Deque &rhs) = default;
    // move constructor
    Deque(Deque &&rhs) = default;
    // move assignment operator
    Deque &operator=(Deque &&rhs) = default;

    // insert element to the front of the deque
    // time complexity O(1)
    void push(const Object & x)
    {
        list.push_front(x);
    }

    // remove the element from the front side
    // and return the element.
    // time complexity O(1)
    void pop(Object & x)
    {
        x = list.front();
        list.pop_front();
    }

    // insert element to the rear end of the deque.
    // time complexity O(1)
    void inject(const Object & x)
    {
        list.push_back(x);
    }

    // Remove the element item from the deque and return it.
    // time complexity O(1)
    void eject(Object & x)
    {
        x = list.back();
        list.pop_back();
    }

    bool empty()
    {
        return list.empty();
    }

    size_t size()
    {
        return list.size();
    }

  private:
    List<Object> list;
};

int
main(int argc, char **argv)
{
    Deque<int> deque;
    for (int i = 0; i < 10; ++i)
    {
        deque.push(2 * i);
        deque.inject(2 * i + 1);
    }

    while(!deque.empty())
    {
        int val;
        deque.pop(val);
        std::cout << val << " ";
    }
    return 0;
}