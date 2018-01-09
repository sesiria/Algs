/*
 * Exercise 1.13
 * Author: sesiria  2018
 * Class template Collection, provide some interface.
 * size,isEmpty, makeEmpty, insert, remove, contains.
 */

#include <iostream>
#include <vector>

template <typename Comparable>
class Collection
{
public:
    explicit Collection(int nSize = 0)
        :m_vec(nSize) // init the size
    {}

    // we used default for the big-five interface.
    ~Collection() = default;
    Collection(const Collection<Comparable> &rhs) = default;
    Collection(Collection<Comparable> &&rhs) = default;
    Collection &operator=(const Collection<Comparable> &rhs) = default;
    Collection &operator=(Collection<Comparable> &&rhs) = default;

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

  private:
    std::vector<Comparable> m_vec;
};

int main(int argc, char ** argv)
{
    Collection<int> collect;
    collect.insert(1);
    collect.insert(2);
    collect.insert(3);
    collect.insert(4);

    if(collect.contains(3))
        std::cout << "Collections contains 3" << std::endl;

    collect.remove(3);

    if(!collect.contains(3))
        std::cout << "Collections doesn't contains 3" << std::endl;

    collect.makeEmpty();
    std::cout << "The size of the collection is " << collect.size() << std::endl;
    return 0;
}