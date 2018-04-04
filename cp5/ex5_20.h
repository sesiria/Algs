/*
* Exercise 5.20 header file
* Author: sesiria  2018
* Implementation of the type dictionary class.
* used the self defined HashTable class.
*/
#ifndef HASH_TABLE_NORMAL_H
#define HASH_TABLE_NORMAL_H

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

bool isPrime(int num)
{
    if (num == 2 || num == 3)
    {
        return true;
    }
    if (num % 6 != 1 && num % 6 != 5)
    {
        return false;
    }
    for (int i = 5; i * i <= num; i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

int nextPrime(int n)
{
    bool state = isPrime(n);
    while (!state)
    {
        state = isPrime(++n);
    }
    return n;
}

/**
 * generic hash function object. for int, float, double
 */
template <typename HashedObj>
class hash
{
  public:
    size_t operator()(const HashedObj &key)
    {
        return static_cast<size_t>(key);
    }
};

/**
 * hash function object for string.
 */
template <>
class hash<std::string>
{
  public:
    size_t operator()(const std::string &key)
    {
        size_t hashVal = 0;

        for (char ch : key)
            hashVal = 37 * hashVal + ch;

        return hashVal;
    }
};

// this is the sample code for the HashTable.
template <typename HashedObj, typename Object>
struct Pair
{
    HashedObj key;
    Object def;

    Pair(const HashedObj &rhs, const Object &obj)
        : key{rhs}, def{obj}
    {
    }

    Pair(HashedObj &&rhs, Object &&obj)
        : key{std::move(rhs)}, def{std::move(obj)}
    {
    }
};

template <typename HashedObj, typename Object>
bool operator==(const Pair<HashedObj, Object> &lhs, const Pair<HashedObj, Object> &rhs)
{
    return lhs.key == rhs.key;
}

template <>
class hash<Pair<std::string, int>>
{
  public:
    size_t operator()(const Pair<std::string, int> &key)
    {
        static hash<std::string> hf;

        return hf(key.key);
    }
};

template <typename HashedObj>
class HashTable
{
  public:
    // the Big five.
    explicit HashTable(int size = 101)
        : theLists(size)
    {
    }

    ~HashTable() = default;

    HashTable(const HashTable &rhs) = default;

    HashTable(HashTable &&rhs) = default;

    HashTable &operator=(const HashTable &rhs) = default;

    HashTable &operator=(HashTable &&rhs) = default;

    void makeEmpty()
    {
        for (auto &thisList : theLists)
            thisList.clear();
    }

    bool contains(const HashedObj &x) const
    {
        auto &whichList = theLists[myhash(x)];
        return std::find(begin(whichList), end(whichList), x) != end(whichList);
    }

    bool remove(const HashedObj &x)
    {
        auto &whichList = theLists[myhash(x)];
        auto itr = find(begin(whichList), end(whichList), x);

        if (itr == end(whichList)) // not found
            return false;

        whichList.erase(itr);
        --currentSize;
        return true;
    }

    bool insert(const HashedObj &x)
    {
        auto &whichList = theLists[myhash(x)];
        if (find(begin(whichList), end(whichList), x) != end(whichList))
            return false; // already existed.

        whichList.push_back(x); // insert the element.

        // Rehash; ref section 5.5
        if (++currentSize > theLists.size())
            rehash();

        return true;
    }

    bool insert(HashedObj &&x)
    {
        auto &whichList = theLists[myhash(x)];
        if (find(begin(whichList), end(whichList), x) != end(whichList))
            return false; // already existed.

        whichList.push_back(std::move(x)); // insert the element.

        // Rehash; ref section 5.5
        if (++currentSize > theLists.size())
            rehash();

        return true;
    }

    void printAll()
    {
        for (auto &thisList : theLists)
            for (auto &x : thisList)
                std::cout << x << " ";
        std::cout << std::endl;
    }

  private:
    std::vector<std::list<HashedObj>> theLists;
    int currentSize;

    /**
    * example for hash template object
    * this is a member function of a class
    * theLists is the size of the hash table.
    */
    size_t myhash(const HashedObj &x) const
    {
        static hash<HashedObj> hf;
        return hf(x) % theLists.size();
    }

    /**
     * Rehashing for separate chaining hash table.
     */
    void rehash()
    {
        std::vector<std::list<HashedObj>> oldList(nextPrime(2 * theLists.size()));
        std::swap(oldList, theLists);
        // Create new double-sized, empty table
        currentSize = 0;
        for (auto &thisList : oldList)
            for (auto &x : thisList)
                insert(std::move(x));
    }
};

#endif