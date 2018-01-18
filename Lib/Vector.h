#ifndef VECTOR_H
#define VECTOR_H
#include <algorithm>

template <typename Object>
class Vector
{
public:
    // one parameter constructor.
    explicit Vector(int initSize = 0)
        : theSize{initSize},
        theCapacity{SPARE_CAPACITY}
    {
        objects = new Object[theCapacity];
    }

    // copy constructor.
    Vector(const Vector& rhs)
        : theSize{rhs.theSize},
        theCapacity{rhs.theCapacity},
        objects{nullptr}
    {
        objects = new Object[theCapacity];
        for (int k = 0; k < theSize; ++k)
            objects[k] = rhs.objects[k];
    }

    // copy assignment operator.
    Vector & operator= (const Vector & rhs)
    {
        Vector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    // destructor.
    ~Vector()
    {
        delete[] objects;
    }

    // Move constructor.
    Vector(Vector && rhs)
        : theSize{rhs.theSize},
        theCapacity{rhs.theCapacity},
        objects{rhs.objects}
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    // Move assignment operator
    Vector & operator= (Vector && rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        std::swap(objects, rhs.objects);

        return *this;
    }

    void resize(int newSize)
    {
        if(newSize > theCapacity)
            reserve(newSize * 2);
        theSize = newSize;
    }

    // enlarge/shrink the allocated memory.
    // allocated a new buffer, and copy all element to new allocated memory buffer.
    void reserve(int newCapacity)
    {
        if(newCapacity < theSize)
            return;

        Object *newArray = new Object[newCapacity];
        for (int k = 0; k < theSize; ++k)
            newArray[k] = std::move(objects[k]);

        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete[] newArray;
    }

    // [] Operator
    Object & operator[] (int index)
    {
        return objects[index];
    }

    const Object & operator[] (int index) const
    {
        return objects[index];
    }

    bool empty() const
    {
        return size() == 0;
    }

    int size() const
    {
        return theSize;
    }

    int capacity() const
    {
        return theCapacity;
    }

    // method for manipulating for element
    void push_back(const Object & x)
    {
        if(theSize == theCapacity)
            reserve(2 * theCapacity + 1); //enlarge the capacity
        objects[theSize++] = x;
    }

    void push_back(Object && x)
    {
        if(theSize == theCapacity)
            reserve(2 * theCapacity + 1); //enlarge the capacity
        objects[theSize++] = std::move(x);
    }

    void pop_back()
    {
        // assert(theSize > 0)
        --theSize;
    }

    const Object& back() const
    {
        // assert(theSize > 0)
        return objects[theSize - 1];
    }

    typedef Object *iterator;
    typedef const Object *const_iterator;

    iterator begin()
    {
        return &objects[0];
    }

    const_iterator begin() const
    {
        return &objects[0];
    }

    iterator end()
    {
        return &objects[size()];
    }

    const_iterator end() const
    {
        return &objects[size()];
    }

    static const int SPARE_CAPACITY = 16;
private:
    int theSize;        // the number of elements in the Vector
    int theCapacity;    // the capacity/size for the allocated memory.
    Object *objects;
};
#endif