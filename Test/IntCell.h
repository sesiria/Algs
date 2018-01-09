#ifndef INTCELL_H
#define INTCELL_H

class IntCell
{
public:
    explicit IntCell(int initialValue = 0)      // Constructor
    { storedValue = new int{initialValue}; }

    ~IntCell()                                  // Destructor
    { delete storedValue; }

    IntCell(const IntCell & rhs)                // Copy constructor
    { storedValue = new int{ *rhs.storedValue}; }

    IntCell(IntCell && rhs)                     // Move constructor
        : storedValue{ rhs.storedValue} 
    { rhs.storedValue = nullptr; }

    IntCell & operator= (const IntCell & rhs)   // Copy assignment
    {
        if( this != &rhs)
            *storedValue = *rhs.storedValue;
        return *this;
    }

    IntCell & operator= ( IntCell && rhs)       // Move assignment
    {
        std::swap( storedValue, rhs.storedValue);
        return *this;
    }
    int read() const
    { return *storedValue ;}

    void write(int x)
    { *storedValue = x; }

private:
    int *storedValue;
};

#endif