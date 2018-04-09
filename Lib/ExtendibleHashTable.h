/*
* Author: sesiria  2018
* hashtable implementation by extensible hash algorithm.
* hash function implementation by universal hash algorithm.
*/
#ifndef EXTENDIBLE_HASHTABLE_H
#define EXTENDIBLE_HASHTABLE_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_set>

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

size_t universalHash(int x, int A, int B, int M)
{
	static const int DIGS = 31;
	static const long mersennep = (1L << DIGS) - 1;

	long long hashVal = static_cast<long long>(A)* x + B;

	hashVal = ((hashVal >> DIGS) + (hashVal & mersennep));
	if (hashVal >= mersennep)
		hashVal -= mersennep;

	return static_cast<size_t>(hashVal) % M;
}

/**
* generic hash function object. for int, float, double
*/
template <typename HashedObj>
class hash
{
public:
	size_t operator()(const HashedObj &key) const
	{
		return static_cast<size_t>(key);
	}

	bool operator()(const HashedObj &lhs, const HashedObj &rhs) const;
};

/**
* hash function object for string.
*/
template <>
class hash<std::string>
{
public:
	size_t operator()(const std::string &key) const
	{
		size_t hashVal = 0;

		for (char ch : key)
			hashVal = 37 * hashVal + ch;

		return hashVal;
	}

	bool operator()(const std::string & lhs, const std::string & rhs) const
	{
		return lhs < rhs;
	}
};


#define PAGE_SZ (200)

template <typename HashedObj, typename HashFunction>
class ExtendibleHashTable
{
public:
	explicit ExtendibleHashTable()
		:globalDepth{ 1 }, array(2, nullptr)
	{
		for (auto &entry : array)
			entry = new HashEntry(1);
	}

    ~ExtendibleHashTable()
    {
        std::unordered_set<HashEntry *> freeList;
        for(auto & entry : array)
            freeList.insert(entry);
        
        for(auto & e : freeList)
            delete e;
    }

	bool contains(const HashedObj & obj) const
	{
		auto entry = getEntry(obj);
		return entry.contains(obj);
	}

	bool insert(const HashedObj & obj)
	{
		HashEntry &entry = getEntry(obj);
		if (entry.contains(obj))
			return false;

		if (entry.isfull() && entry.localDepth == globalDepth)
		{
			expand();
			++globalDepth;
		}

		if (entry.isfull() && entry.localDepth < globalDepth)
		{
			entry.insert(obj);
			// split the elements into two
			HashEntry *p1 = new HashEntry(1);
			HashEntry *p2 = new HashEntry(1);

			for (auto &e : entry.elements)
			{
				auto hashVal = myhash(e);
				hashVal &= ((1U << globalDepth) - 1);
				if ((hashVal >> entry.localDepth) & 1)
					p2->insert(e);
				else
					p1->insert(e);
			}

			int idx = 0;
			for (auto & x : array)
			{
				if (x == &entry)
				{
					if ((idx >> entry.localDepth) & 1)
						array[idx] = p2;
					else
						array[idx] = p1;
				}
				++idx;
			}

			p2->localDepth = p1->localDepth = entry.localDepth + 1;

			// free the old entry
			delete &entry;
		}
		else
			return entry.insert(obj);

		return true;
	}

private:
	/* the HashEntry is stand for the page */
	struct HashEntry
	{
		std::unordered_set<HashedObj> elements;
		int localDepth;

		HashEntry(int depth)
			: localDepth{ depth }
		{
		}

		bool isfull()
		{
			return elements.size() >= PAGE_SZ;
		}

		bool contains(const HashedObj & obj) const
		{
			if (elements.find(obj) != elements.end())
				return true;
			else
				return false;
		}

		bool insert(const HashedObj & obj)
		{
			if (contains(obj))
				return false;

			return elements.insert(obj).second;
		}
	};

	int globalDepth;
	std::vector<HashEntry*> array;

	const HashEntry& getEntry(const HashedObj &obj) const
	{
		auto hashVal = myhash(obj);
		return *array[hashVal & ((1UL << globalDepth) - 1)];
	}

	HashEntry& getEntry(const HashedObj &obj)
	{
		auto hashVal = myhash(obj);
		return *array[hashVal & ((1UL << globalDepth) - 1)];
	}

	size_t getEntryPos(const HashedObj & obj) const
	{
		auto hashVal = myhash(obj);
		return hashVal & ((1UL << globalDepth) - 1);
	}

	size_t myhash(const HashedObj &x) const
	{
		static hash<HashedObj> hf;
		return universalHash(hf(x), 31, 7932, array.size());
	}

	void expand()
	{
		std::vector<HashEntry *> oldArray(array.size() * 2);

		std::swap(oldArray, array);

		for (decltype(oldArray.size()) idx = 0; idx != oldArray.size(); ++idx)
		{
			array[idx] = oldArray[idx];
			array[idx + oldArray.size()] = oldArray[idx];
		}
	}
};

#endif