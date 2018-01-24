/*
 * Exercise 3.24
 * Author: sesiria  2018
 * use only one array to implement two stacks.
 */
#include <iostream>
#include <exception>

class StackOverflowException : std::exception
{
public:
    virtual const char * what() const noexcept
    {
        return "stack overflow!";
    }
};

class AccessEmptyStackException : std::exception
{
public:
    virtual const char * what() const noexcept
    {
        return "empty stack!";
    }
};

template <typename Object>
class DoubleStack
{
  public:
    // default constructor.
    explicit DoubleStack(size_t theCapacity = defaultCapacity)
     : m_thecapacity{theCapacity},
     posFront{0},
     posEnd{theCapacity - 1}
    {
        m_array = new Object[theCapacity];
    }

    // destructor
    ~DoubleStack()
    {
        delete[] m_array;
    }

    // copy constructor
    DoubleStack(const DoubleStack & rhs)
        : m_thecapacity{rhs.m_thecapacity},
            posFront{rhs.posFront},
            posEnd(rhs.posEnd)
    {
        m_array = new Object[m_thecapacity];
        // copy data
        for (int i = 0; i < posFront; ++i)
            m_array[i] = rhs.m_array[i];
        for (int j = m_thecapacity - 1; j > posEnd; --j)
            m_array[j] = rhs.m_array[j];
    }

    // copy assignment operator
    DoubleStack & operator= (const DoubleStack &rhs)
    {
        DoubleStack copy = rhs;
        std::swap(copy, *this);
        return *this;
    }

    // move constructor
    DoubleStack(DoubleStack && rhs)
        : m_array{rhs.m_array},
        m_thecapacity{rhs.m_thecapacity},
        posFront{rhs.posFront},
        posEnd{rhs.posEnd}
    {
        rhs.m_array = nullptr;
        rhs.m_thecapacity = 0;
        rhs.posFront = 0;
        rhs.posEnd = 0;
    }

    // move assignment operator
    DoubleStack & operator= (DoubleStack && rhs)
    {
        std::swap(m_array, rhs.m_array);
        std::swap(m_thecapacity, rhs.m_thecapacity);
        std::swap(posFront, rhs.posFront);
        std::swap(posEnd, rhs.posEnd);
    }

    void push_front(const Object & x)
    {
        if(isOverflow())
            throw StackOverflowException{};
        m_array[posFront++] = x;
    }

    void push_end(const Object & x)
    {
        if(isOverflow())
            throw StackOverflowException{};
        m_array[posEnd--] = x;
    }

    void pop_front()
    {
        if(isFrontEmpty())
            throw AccessEmptyStackException{};
        posFront--;
    }

    void pop_end()
    {
        if(isFrontEmpty())
            throw AccessEmptyStackException{};
        posEnd++;
    }

    const Object & front() const
    {
        if(isFrontEmpty())
            throw AccessEmptyStackException{};
        return m_array[posFront - 1];
    }

    Object & front()
    {
        if(isFrontEmpty())
            throw AccessEmptyStackException{};
        return m_array[posFront - 1];
    }


    const Object & end() const
    {
        if(isEndEmpty())
            throw AccessEmptyStackException{};
        return m_array[posEnd + 1];
    }

    Object & end()
    {
        if(isEndEmpty())
            throw AccessEmptyStackException{};
        return m_array[posEnd + 1];
    }

    bool isFrontEmpty() const
    {
        return posFront == 0;
    }

    bool isEndEmpty() const
    {
        return posEnd == (m_thecapacity - 1);
    }


  private:
    const static size_t defaultCapacity = 100;
    Object *    m_array;
    size_t      m_thecapacity;
    size_t      posFront;        // pos for stack front.
    size_t      posEnd;         // pos for stack end.

    // check overflow
    bool isOverflow()
    {
        return (posFront > posEnd);
    }
};

int
main(int argc, char **argv)
{
    DoubleStack<int> stack(100);
    for (int i = 0; i < 50; ++i)
    {
        stack.push_front(2 * i);
        stack.push_end(2 * i + 1);
    }

    // this code will cause an stackoverflow.
    stack.push_front(101);
    return 0;
}