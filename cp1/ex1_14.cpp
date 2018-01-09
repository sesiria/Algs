/*
 * Exercise 1.14
 * Author: sesiria  2018
 * Class template OrderCollection provide some interface.
 * size,isEmpty, makeEmpty, insert, remove, contains.
 * findMin, findMax return the reference to the min and max element.
 */

#include <iostream>
#include <vector>
#include <assert.h>


template <typename Comparable>  
void bubblesort(std::vector<Comparable>& arr) {  
    for (int i = 0; i < arr.size(); i++) {  
        for(int j = 0; j < arr.size() - i - 1; j++) {  
            if(arr[j] > arr[j + 1])  
                std::swap(arr[j], arr[j + 1]) ;
        }  
    }  
}

// note that the implementation of the OrderCollection is not effective. 
// because it will sort the element everytime.(in an Array)
// I will modify the data structure to a balanced binary tree to
// store the elemtn later.
template <typename Comparable>
class OrderCollection
{
public:
    explicit OrderCollection(int nSize = 0)
        :m_vec(nSize) // init the size
    {
    }

    // we used default for the big-five interface.
    ~OrderCollection() = default;
    OrderCollection(const OrderCollection<Comparable> &rhs) = default;
    OrderCollection(OrderCollection<Comparable> &&rhs) = default;
    OrderCollection &operator=(const OrderCollection<Comparable> &rhs) = default;
    OrderCollection &operator=(OrderCollection<Comparable> &&rhs) = default;

    size_t size()
    {
        return m_vec.size();
    }

    bool isEmpty()
    {
        return (m_vec.size() == 0);
    }

    void makeEmpty()
    {
        m_vec.clear();
    }

    void insert(Comparable obj)
    {
        m_vec.push_back(obj);
        bubblesort(m_vec);
    }

    void remove(Comparable obj)
    {
        typename std::vector<Comparable>::iterator iter;
        for (iter = m_vec.begin(); iter != m_vec.end();)
        {
            if(*iter == obj) {
                iter = m_vec.erase(iter);     
            } else{
                ++iter;
            }      
        }
        bubblesort(m_vec);
    }

    bool contains(Comparable obj) const
    {
        for (int i = 0; i < m_vec.size(); i++)
        {
            if(m_vec[i] == obj)
                return true;
        }
        return false;
    }

    Comparable & findMin() throw()
    {
        if(m_vec.size() == 0)
            assert(0);
        return m_vec[0];
    }

    Comparable & findMax() throw()
    {
        if(m_vec.size() == 0)
            assert(0);
        return m_vec[m_vec.size() - 1];
    }

private:
    std::vector<Comparable> m_vec;
};

int main(int argc, char ** argv)
{
    OrderCollection<int> collect{0};
    collect.insert(3);
    collect.insert(1);
    collect.insert(4);
    collect.insert(2);
 
    std::cout << "The min element is " << collect.findMin() << std::endl;
    std::cout << "The max element is " << collect.findMax() << std::endl;
    return 0;
}

