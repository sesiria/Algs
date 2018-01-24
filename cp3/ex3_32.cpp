/*
 * Exercise 3.32
 * Author: sesiria  2018
 * Queue implementation by singly-linklist
 * with no header or tail nodes.
 */
#include <iostream>
#include <exception>

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
          front{nullptr},
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
          front{nullptr},
          back{nullptr}
    {
        Node *p = rhs.front;
        while (p != nullptr)
        {
            enqueue(p->data);
            p = p->next;
        }            
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
          front{rhs.front},
          back{rhs.back}
    {
        rhs.theSize = 0;
        rhs.front = nullptr;
        rhs.back = nullptr;
    }

    // move assignment operator
    Queue &operator=(Queue &&rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(front, rhs.front);
        std::swap(back, rhs.back);
        return *this;
    }

    // enqueue a new element to the back of Queue.
    void enqueue(const Object &x)
    {
        Node *p = new Node{x, nullptr};
        if (theSize == 0) // if it is a empty linklist.
        {
            front = back = p;
        }
        else
        {
            back = back->next = p;
        }
        ++theSize;
    }

    // remove the element from the front of the Queue.
    Object dequeue()
    {
        if (empty())
            throw QueueUnderflowException{};
        Node *p = front;
        Object val = p->data;
        front = front->next;
        --theSize;
        if (theSize == 0)
            back = nullptr;
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
    Node *front;
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