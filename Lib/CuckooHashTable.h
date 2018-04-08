/*
* Author: sesiria  2018
* hashtable implementation by cuckoo hashing algorithm.
* this implementation will support by multi-thread implementation.
*/
#ifndef CUCKOO_HASHTABLE_H
#define CUCKOO_HASHTABLE_H

#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include "UniformRandom.h"

// utility function nextPrime

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


// Generic HashFamily interface for cuckoo hashing
template <typename AnyType>
class CuckooHashFamily
{
  public:
    size_t hash(const AnyType &x, int which) const;
    int getNumberOfFunctions();
    void generateNewFunctions();
};


template <int count>
class StringHashFamily
{
  public:
    StringHashFamily() : MULTIPLIERS(count)
    {
        generateNewFunctions();
    }

    int getNumberOfFunctions() const
    {
        return count;
    }

    void generateNewFunctions()
    {
        for(auto & mult : MULTIPLIERS)
            mult = r.nextInt();
    }

    size_t hash(const std::string & x, int which) const
    {
        const int multiplier = MULTIPLIERS[which];
        size_t hashVal = 0;

        for(auto ch : x)
            hashVal = multiplier * hashVal + ch;

        return hashVal;
    }

  private:
    std::vector<int> MULTIPLIERS;
    UniformRandom r;
};



// Cuckoo hashing table interface.
template <typename AnyType, typename HashFamily>
class CuckooHashTable
{
  public:
    explicit CuckooHashTable(int size = 101)
        : array(nextPrime(size))
    {
        numHashFunctions = hashFunctions.getNumberOfFunctions();
        rehashes = 0;
        makeEmpty();
    }

    void makeEmpty()
    {
        currentSize = 0;
        for(auto &entry : array)
            entry.isActive = false;
    }

    /**
     * Return true if x is found.
     */ 
    bool contains(const AnyType &x) const
    {
        return findPos(x) != -1;
    }

    /**
     * Remove x from the hash table.
     * Return true if item was found and removed.
     */ 
    bool remove(const AnyType &x)
    {
        int currentPos = findPos(x);
        if(!isActive(currentPos))
            return false;

        array[currentPos].isActive = false;
        --currentSize;
        return true;
    }

    bool insert(const AnyType &x)
    {
        if(contains(x))
            return false;
        
        if(currentSize >= array.size() * MAX_LOAD)
            expand();

        return insertHelper1(x);
    }

    bool insert(AnyType &&x)
    {
         if(contains(x))
            return false;
        
        if(currentSize >= array.size() * MAX_LOAD)
            expand();

        return insertHelper1(std::move(x));       
    }

    int size() const
    {
        return currentSize;
    }

    int capacity() const
    {
        return array.size();
    }

  private:
    struct HashEntry
    {
        AnyType element;
        bool isActive;

        HashEntry(const AnyType & e = AnyType(), bool a = false)
          :element{e}, isActive{a}
        {}

        HashEntry(AnyType &&e, bool a = false)
          :element{std::move(e)}, isActive{a}
        {}
    };

    bool insertHelper1(const AnyType &xx)
    {
        constexpr int COUNT_LIMIT = 100;
        AnyType x = xx;

        while(true)
        {
            int lastPos = -1;
            int pos;

            for (int count = 0; count < COUNT_LIMIT; ++count)
            {
                for (int i = 0; i < numHashFunctions; ++i)
                {
                    pos = myhash(x, i);

                    if(!isActive(pos))
                    {
                        array[pos] = std::move(HashEntry{std::move(x), true});
                        ++currentSize;
                        return true;
                    }
                }

                // None of the spots are available. Evict a random one
                int i = 0;
                do{
                    pos = myhash(x, r.nextInt(numHashFunctions));
                } while (pos == lastPos && i++ < 5);

                lastPos = pos;
                std::swap(x, array[pos].element);
            }

            if(++rehashes > ALLOWED_REHASHES)
            {
                expand();       // Make the table bigger
                rehashes = 0;   // Reset the # of rehashes
            } else
                rehash();       // Same table size, new hash functions.
        }
    }

    bool insertHelper1(AnyType &&x)
    {
        constexpr int COUNT_LIMIT = 100;

        while(true)
        {
            int lastPos = -1;
            int pos;

            for (int count = 0; count < COUNT_LIMIT; ++count)
            {
                for (int i = 0; i < numHashFunctions; ++i)
                {
                    pos = myhash(x, i);

                    if(!isActive(pos))
                    {
                        array[pos] = std::move(HashEntry{std::move(x), true});
                        ++currentSize;
                        return true;
                    }
                }

                // None of the spots are available. Evict a random one
                int i = 0;
                do{
                    pos = myhash(x, r.nextInt(numHashFunctions));
                } while (pos == lastPos && i++ < 5);

                lastPos = pos;
                std::swap(x, array[pos].element);
            }

            if(++rehashes > ALLOWED_REHASHES)
            {
                expand();       // Make the table bigger
                rehashes = 0;   // Reset the # of rehashes
            } else
                rehash();       // Same table size, new hash functions.
        }
    }

    bool isActive(int currentPos) const
    {
        return currentPos != -1 && array[currentPos].isActive;
    }

    /**
     * Compute the hash code for x using specified function.
     */ 
    size_t myhash(const AnyType &x, int which) const
    {
        return hashFunctions.hash(x, which) % array.size();
    }

    /**
     * Search all hash function places. Return the position
     * where the search terminates or -1 if not found.
     */ 
    int findPos(const AnyType &x) const
    {
        for (int i = 0; i < numHashFunctions; ++i)
        {
            int pos = myhash(x, i);
            if(isActive(pos) && array[pos].element == x)
                return pos;
        }
        return -1;
    }

    void expand()
    {
        rehash(static_cast<int>(array.size() / MAX_LOAD));
    }

    void rehash()
    {
        hashFunctions.generateNewFunctions();
        rehash(array.size());
    }

    void rehash(int newSize)
    {
        std::vector<HashEntry> oldArray(nextPrime(newSize));

        // swap the array with the current.
        std::swap(oldArray, array);

        makeEmpty();

        // Copy table over
        currentSize = 0;
        for(auto & entry : oldArray)
            if(entry.isActive)
                insert(std::move(entry.element));
    }

    static constexpr double MAX_LOAD = 0.40;
    static constexpr int ALLOWED_REHASHES = 5;

    std::vector<HashEntry> array;
    int currentSize;
    int numHashFunctions;
    int rehashes;
    UniformRandom r;
    HashFamily hashFunctions;
};

#endif
