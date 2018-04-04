/*
* Exercise 5.20 source file
* Author: sesiria  2018
* Implementation of the type dictionary class.
* used the self defined HashTable class.
*/

#include <iostream>
#include <string.h>
#include <string>
#include "ex5_20.h" // chain linklist hashtable

using namespace std;

template <typename HashedObj, typename Object>
class Dictionary
{
  public:
    Dictionary()
    {

    }

    void insert(const HashedObj &key, const Object &definition)
    {
        items.insert(Pair<HashedObj, Object>(key, definition));
    }

    bool lookup(const HashedObj &key) const
    {
        return items.contains(Pair<HashedObj, Object>(key, Object{}));
    }

    bool isEmpty() const
    {
        return items.isEmpty();
    }

    void makeEmpty()
    {
        items.makeEmpty();
    }

  private:
    HashTable<Pair<HashedObj, Object>> items;
};

int main()
{
    Dictionary<string, int> table;
    table.insert("a", 5);
    std::cout << table.lookup("a") << std::endl;
    return 0;
}

