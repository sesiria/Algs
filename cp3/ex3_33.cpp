/*
 * Exercise 3.33
 * Author: sesiria  2018
 * Queue implementation by circular theArray.
 * with no header or tail nodes.
 */
#include <exception>
#include <iostream>
#include <vector>

class QueueUnderflowException : std::exception
{
  public:
    virtual const char *what() const noexcept
    {
        return "Queue underflow!";
    }
};

template <typename Object>
class Queue
{
  private:
    const static size_t theDefaultCapacity = 10;

  public:
    // default constructor.
    explicit Queue(size_t capacity = theDefaultCapacity)
        : theCapacity{capacity},
          theSize{0},
          front{0},
          back{theCapacity - 1},
          theArray((int)theCapacity)
    {
    }

    // destructor
    ~Queue() = default;

    // copy constructor
    Queue(const Queue &rhs) = default;
    // copy assignment operator
    Queue &operator=(const Queue &rhs) = default;
    // move constructor
    Queue(Queue &&rhs):
          theCapacity{rhs.theCapacity},
          theSize{rhs.theSize},
          front{rhs.front},
          back{rhs.back},
          theArray(std::move(rhs.theArray))
    {
        rhs.theCapacity = 0;
        rhs.theSize = 0;
        rhs.front = 0;
        rhs.back = 0;
    }

    // move assignment operator
    Queue &operator=(Queue &&rhs) = default;

    // enqueue a new element to the back of Queue.
    void enqueue(const Object &x)
    {
        if(back == (theCapacity - 1))
            back = 0;
        else
            back++;
        theArray[back] = x;
        theSize++;
    }

    // remove the element from the front of the Queue.
    Object dequeue()
    {
        if(empty())
            throw QueueUnderflowException{};
        Object val = theArray[front];
        if(front == (theCapacity - 1))
            front = 0;
        else
            front++;

        theSize--;
        return val;
    }

    bool empty()
    {
        return theSize == 0;
    }

    size_t size()
    {
        return theSize;
    }

  private:
    size_t theCapacity;
    size_t theSize;
    size_t front;
    size_t back;
    std::vector<Object> theArray;
};

int main(int argc, char **argv)
{
    Queue<int> queue;
    for (int i = 0; i < 10; ++i)
        queue.enqueue(i);
    Queue<int> queue1 = queue;
    Queue<int> queue2 = std::move(queue1);
    while (!queue.empty())
    {
        std::cout << queue.dequeue() << " ";
    }
    std::cout << std::endl;

    while (!queue1.empty())
    {
        std::cout << queue1.dequeue() << " ";
    }
    while (!queue2.empty())
    {
        std::cout << queue2.dequeue() << " ";
    }
    return 0;
}