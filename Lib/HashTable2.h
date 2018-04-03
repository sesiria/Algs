/*
* Author: sesiria  2018
* hashtable implementation by probing strategies.
*/

#ifndef HASH_TABLE_PROBING_H
#define HASH_TABLE_PROBING_H

#include <algorithm>
#include <math.h>
#include <string>
#include <vector>
#include <iostream>

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

//

template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable(int size = 101)
        : array(nextPrime(size))
    {
        makeEmpty();
    }

    bool contains(const HashedObj &x) const
    {
        return isActive(findPos(x));
    }

    void makeEmpty()
    {
        currentSize = 0;
        for (auto &entry : array)
            entry.info = EMPTY;
    }

    bool insert(const HashedObj &x)
    {
        // insert x as active
        int currentPos = findPos(x);
        if (isActive(currentPos))
            return false;

        array[currentPos].element = x;
        array[currentPos].info = ACTIVE;

        // Rehash; ref section 5.5
        if (++currentSize > array.size() / 2)
            rehash();

        return true;
    }

    bool insert(HashedObj &&x)
    {
        // insert x as active
        int currentPos = findPos(x);
        if (isActive(currentPos))
            return false;

        array[currentPos].element = std::move(x);
        array[currentPos].info = ACTIVE;

        // Rehash; ref section 5.5
        if (++currentSize > array.size() / 2)
            rehash();

        return true;
    }

    // lazy deletion for remove.
    bool remove(const HashedObj &x)
    {
        int currentPos = findPos(x);
        if(!isActive(currentPos))
            return false;

        array[currentPos].info = DELETED;
        return true;
    }

    enum EntryType
    {
        ACTIVE,
        EMPTY,
        DELETED
    };

    void printAll()
    {
        for(auto & entry : array)
            if(entry.info == ACTIVE) // ignored the element is lazy deleted.
                std::cout << entry.element << " ";
        std::cout << std::endl;
    }

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY)
            : element{e}, info{i}
        {
        }

        HashEntry(HashedObj &&e, EntryType i = EMPTY)
            : element{std::move(e)}, info{i}
        {
        }
    };

    std::vector<HashEntry> array;
    int currentSize = 0;

    bool isActive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }

    // hashing with quadratic probing
    int findPos(const HashedObj &x) const
    {
        int offset = 1;
        int currentPos = myhash(x);

        while (array[currentPos].info != EMPTY &&
               array[currentPos].element != x)
        {
            currentPos += offset; // Compute the ith probe
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }

        return currentPos;
    }


    /**
     * Rehashing for quadratic probing hash table.
     */ 
    void rehash()
    {
        std::vector<HashEntry> oldArray(nextPrime(2 * array.size()));
        std::swap(oldArray, array);

        makeEmpty();

        // copy table over
        currentSize = 0;
        for(auto & entry : oldArray)
            if(entry.info == ACTIVE) // ignored the element is lazy deleted.
                insert(std::move(entry.element));
    }

    size_t myhash(const HashedObj &x) const
    {
        static hash<HashedObj> hf;
        return hf(x) % array.size();
    }
};

#endif