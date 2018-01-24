/*
 * Exercise 3.25
 * Author: sesiria  2018
 * ExtendStack support push pop and findMin 
 * All rountine above with time complexity O(1)
 * sub problem (b) is unsolved since it require the material chapter 7.
 */
#include <iostream>
#include <exception>
#include <stack>


class StackUnderflowException : std::exception
{
public:
    virtual const char * what() const noexcept
    {
        return "stack underflow!";
    }
};

template <typename Comparable>
class ExtendStack
{
  public:
    // default constructor.
    ExtendStack() = default;
    // destructor
    ~ExtendStack() = default;
    // copy constructor
    ExtendStack(const ExtendStack &rhs) = default;
    // copy assignment operator
    ExtendStack &operator=(const ExtendStack &rhs) = default;
    // move constructor
    ExtendStack(ExtendStack &&rhs) = default;
    // move assignment operator
    ExtendStack &operator=(ExtendStack &&rhs) = default;

    void push(const Comparable & x)
    {
        if(m_min.empty() || x <= m_min.top())
            m_min.push(x);
        m_data.push(x);
    }

    void pop()
    {
        if(isEmpty())
            throw StackUnderflowException{};
        
        if(m_min.top() == m_data.top())
            m_min.pop();
        m_data.pop();
    }

    const Comparable & top() const
    {
        if(isEmpty())
            throw StackUnderflowException{};
        return m_data.top();
    }

    bool isEmpty() const
    {
        return m_data.empty();
    }

    // time complexity O(1).
    const Comparable & findMin() const
    {
        return m_min.top();
    }

  private:
    std::stack<Comparable> m_data;
    std::stack<Comparable> m_min;
};

int
main(int argc, char **argv)
{
    ExtendStack<int> stack;
    for (int i = 0; i < 50; ++i)
    {
        stack.push(2 * i);
    }

    // this code will cause an stackoverflow.
    stack.push(101);
    return 0;
}