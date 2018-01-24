/*
 * Exercise 3.31
 * Author: sesiria  2018
 * Stack implementation by singly-linklist
 * with no header or tail nodes.
 */
#include <iostream>
#include <exception>

class StackUnderflowException : std::exception
{
  public:
    virtual const char *what() const noexcept
    {
        return "stack underflow!";
    }
};

template <typename Object>
class Stack
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
    Stack()
        : theSize{0},
          first{nullptr}
    {
    }

    // destructor
    ~Stack()
    {
        while (!empty())
            pop();
    }

    // copy constructor
    Stack(const Stack &rhs)
        : theSize{rhs.theSize},
          first{nullptr}
    {
        if (rhs.first == nullptr) // empty linklist.
            return;

        // special case for first node
        first = new Node{rhs.first->data, nullptr};
        Node *prev = first;
        Node *p = rhs.first->next;
        while (p != nullptr)
        {
            prev->next = new Node{p->data, nullptr};
            prev = prev->next;
            p = p->next;
        }
    }

    // copy assignment operator
    Stack &operator=(const Stack &rhs)
    {
        Stack copy = rhs;
        std::swap(copy, *this);
        return *this;
    }
    // move constructor
    Stack(Stack &&rhs)
        : theSize{rhs.theSize},
          first{rhs.first}
    {
        rhs.theSize = 0;
        rhs.first = nullptr;
    }

    // move assignment operator
    Stack &operator=(Stack &&rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(first, rhs.first);
        return *this;
    }

    // push a new element to the top of stack.
    void push(const Object &x)
    {
        first = new Node{x, first};
        ++theSize;
    }

    // remove the element from the top of the stack.
    void pop()
    {
        if (empty())
            throw StackUnderflowException{};
        Node *p = first;
        first = first->next;
        --theSize;
        delete p;
    }

    Object &top()
    {
        if (empty())
            throw StackUnderflowException{};
        return first->data;
    }

    const Object &top() const
    {
        if (empty())
            throw StackUnderflowException{};
        return first->data;
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
    Node *first;
};

int main(int argc, char **argv)
{
    Stack<int> stack;
    for (int i = 0; i < 10; ++i)
        stack.push(i);
    Stack<int> stack1 = stack;
    Stack<int> stack2 = std::move(stack1);
    while (!stack.empty())
    {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << std::endl;

    while (!stack1.empty())
    {
        std::cout << stack1.top() << " ";
        stack1.pop();
    }
    while (!stack2.empty())
    {
        std::cout << stack2.top() << " ";
        stack2.pop();
    }
    return 0;
}