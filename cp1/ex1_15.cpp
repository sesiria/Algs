/*
 * Exercise 1.15
 * Author: sesiria  2018
 * Class rectangle with the interface.
 * getLength and getWidth.
 */
#include <iostream>
#include <vector>




class Rectangle
{
public:
    Rectangle(int nLength, int nWidth)
        :m_nLength{nLength},
        m_nWidth{nWidth}
    {
    }

    int getLength() const
    {
        return m_nLength;
    }

    int getWidth() const
    {
        return m_nWidth;
    }

    // we use the default of the big-five interface
private:
    int m_nLength;
    int m_nWidth;
};

// Generic findMax, with a function object, C++ style.  
// Precondition: a.size() > 0.  
template <typename Object, typename Comparator>  
const Object & findMax(const std::vector<Object> & arr, Comparator isLessThan)  
{  
    int maxIndex = 0;  
  
    for(int i = 1; i < arr.size(); ++i)  
        if(isLessThan(arr[maxIndex], arr[i]))  
            maxIndex = i;  
    return arr[maxIndex];  
}

class CompareArea 
{  
public:  
    bool operator()(const Rectangle& lhs, const Rectangle& rhs) const  
    { return (lhs.getLength() * lhs.getWidth()) < (rhs.getLength() * rhs.getWidth());}  
};

class ComparePerimeter
{  
public:  
    bool operator()(const Rectangle& lhs, const Rectangle& rhs) const  
    { return (lhs.getLength() + lhs.getWidth()) < (rhs.getLength() + rhs.getWidth());}  
};

int main(int argc, char ** argv)
{
    std::vector<Rectangle> arr = 
    {Rectangle{5, 5}, Rectangle{2, 7}, Rectangle{2, 11}};

    const Rectangle & maxArea = findMax(arr, CompareArea{});
    printf("The max area rectangle is %d * %d\n", 
        maxArea.getLength(), maxArea.getWidth());

    const Rectangle & maxPerimeter = findMax(arr, ComparePerimeter{});
    printf("The max perimeter rectangle is %d\n", 
        2 * (maxPerimeter.getLength() + maxPerimeter.getWidth()));
    return 0;
}
