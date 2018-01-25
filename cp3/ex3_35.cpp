/*
 * Exercise 3.35
 * Author: sesiria  2018
 * Queue implementation by circular linklist
 * store only one iterator to the end(back).
 * with no header or tail nodes.
 */
#include <exception>
#include <iostream>

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
    struct Node
    {
        Object data;
        Node *next;
        Node(const Object &x, Node *n = nullptr)
            : data{x},
              next{n}
        {
        }
    };

  public:
    // default constructor.
    Queue()
        : theSize{0},
          back{nullptr}
    {
    }

    // destructor
    ~Queue()
    {
        while (!empty())
            dequeue();
    }

    // copy constructor
    Queue(const Queue &rhs)
        : theSize{0},
          back{nullptr}
    {
        if (rhs.back == nullptr) // empty list
            return;
        Node *p = rhs.back->next; // point to first element.
        for (int i = 0; i < rhs.theSize && p != nullptr;
             ++i, p = p->next)
            enqueue(p->data);
    }

    // copy assignment operator
    Queue &operator=(const Queue &rhs)
    {
        Queue copy = rhs;
        std::swap(copy, *this);
        return *this;
    }
    // move constructor
    Queue(Queue &&rhs)
        : theSize{rhs.theSize},
          back{rhs.back}
    {
        rhs.theSize = 0;
        rhs.back = nullptr;
    }

    // move assignment operator
    Queue &operator=(Queue &&rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(back, rhs.back);
        return *this;
    }

    // enqueue a new element to the back of Queue.
    // time complexity O(1)
    void enqueue(const Object &x)
    {
        Node *p = new Node{x, nullptr};
        if (back == nullptr) // first insertion.
        {
            p->next = p;
            back = p;
        }
        else
        {
            p->next = back->next; // point to the first node.
            back->next = p;
            back = p;
        }
        ++theSize;
    }

    // remove the element from the front of the Queue.
    // time complexity O(1)
    Object dequeue()
    {
        if (empty())
            throw QueueUnderflowException{};
        Node *p = back->next; // store the first element.
        Object val = p->data;
        back->next = p->next; // skip the first element.
        --theSize;
        if (theSize == 0)
            back = nullptr; // special case for zero element.
        delete p;
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
    size_t theSize;
    Node *back;
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
    for (int i = 0; i < 10; ++i)
        queue.enqueue(2 * i);
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