/*
* Author: sesiria  2018
* hashtable implementation by hopscotch hash algorithm.
* hash function implementation by universal hash algorithm.
* this implementation will support by multi-thread implementation.
* Note: normal or simple hash function will cause the performance very pool.
* so we choose the universal hash function.
*/
#ifndef HOPSCOTCH_HASHTABLE_H
#define HOPSCOTCH_HASHTABLE_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
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


size_t universalHash(int x, int A, int B, int M)
{
    static const int DIGS = 31;
    static const int mersennep = static_cast<int>((1L << DIGS) - 1);

    long long hashVal = static_cast<long long>(A) * x + B;

    hashVal = ((hashVal >> DIGS) + (hashVal & mersennep));
    if(hashVal >= mersennep)
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
	size_t operator()(const HashedObj &key);
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

template <typename HashedObj>
class HopscotchHashTable
{
public:
	// the Big five.
	explicit HopscotchHashTable(int size = 101, int dist = 4)
		: array(nextPrime(size)), max_dist{ dist }
	{
		if (dist > MAX_DISTANCE || dist < 0)
		{
			char buf[BUFSIZ] = { 0 };
			sprintf(buf, "Max distance must between 0 ~%d!", MAX_DISTANCE);
			std::string str = buf;
			throw std::runtime_error(str.c_str());
		}
	}

	void makeEmpty()
	{
		for (auto &entry : array)
		{
			entry.hopsField = 0;
			entry.isActive = false;
		}
	}

	bool contains(const HashedObj &x) const
	{
		return findPos(x) != -1;
	}

	bool remove(const HashedObj &x)
	{
		int currentPos = findPos(x);
		// if we not found the element.
		if (!isActive(currentPos))
			return false;

		int originPos = myhash(x);
		int dist = (currentPos + array.size() - originPos) % array.size();

		array[originPos].clearHops(dist);
		array[currentPos].isActive = false;
		--currentSize;
		return true;
	}

	bool insert(const HashedObj &x)
	{
		if (contains(x))
			return false;

		return insertHelper1(x);
	}

	bool insert(HashedObj &&x)
	{
		if (contains(x))
			return false;

		return insertHelper1(std::move(x));
	}

	void printAll()
	{
		for (auto &entry : array)
			std::cout << entry.element << " ";
		std::cout << std::endl;
	}

	int capacity() const
	{
		return array.size();
	}

private:
	struct HashEntry
	{
		HashedObj element;
		unsigned int hopsField;
		bool isActive;

		HashEntry(const HashedObj &e = HashedObj(), unsigned int h = 0, bool a = false)
			: element(e), hopsField(h), isActive(a)
		{
		}

		HashEntry(HashedObj &&e, unsigned int &&h, bool a = false)
			: element(std::move(e)), hopsField(h), isActive(a)
		{
		}

		void setHops(unsigned pos)
		{
			hopsField |= (1U << pos);
		}

		void clearHops(unsigned pos)
		{
			hopsField &= ~(1U << pos);
		}

		bool getHops(unsigned pos) const
		{
			return static_cast<bool>(hopsField & (1U << pos));
		}
	};

	std::vector<HashEntry> array;
	int currentSize;
	int max_dist;
	double MAX_LOAD = 0.5;
	int MAX_DISTANCE = 32;
    hash<HashedObj> hashObj;

    int findPos(const HashedObj &x) const
	{
		auto pos = myhash(x);
		for (int i = 0; i < max_dist; ++i)
			if (array[pos].getHops(i) && array[advanceDist(pos, i)].element == x)
				return advanceDist(pos, i);
		return -1;
	}

	int findInsertionPos(const HashedObj &x) const
	{
		int currentPos = myhash(x);

		while (array[currentPos].isActive)
		{
			++currentPos;
			if (currentPos >= array.size())
				currentPos -= array.size();
		}

		return currentPos;
	}

	bool isActive(const int currentPos) const
	{
		return currentPos != -1 && array[currentPos].isActive;
	}

	size_t myhash(const HashedObj &x) const
	{
		static hash<HashedObj> hf; 
        return  universalHash(hf(x), 31, 7932, array.size());
	}

	bool insertHelper1(const HashedObj &xx)
	{
		int currentPos = findInsertionPos(xx);
		int originPos = myhash(xx);
		int dist = 0; // the distance is legal.

		while (true)
		{
			if ((dist = getDist(currentPos, originPos)) < max_dist)
			{
				array[originPos].setHops(dist);
				array[currentPos].element = xx;
				array[currentPos].isActive = true;
				break;
			}
			else
			{ // do the rearrange.
				int posStart;
				for (posStart = advanceDist(currentPos, 1 - max_dist);
					posStart != currentPos; posStart = advanceDist(posStart, 1))
				{
					// check that the element is evitable.
					int offset = -1;
					if ((offset = isEvitable(posStart, currentPos)) != -1)
					{
						// evitable the elements.
						evitElement(posStart, offset, getDist(currentPos, posStart));

						break;
					}
				}

				if (posStart == currentPos) // fail to evit any element.
				{
					rehash();
					currentPos = findInsertionPos(xx);
					originPos = myhash(xx);
				}
				else
				{
					currentPos = posStart;
				}
			}
		}

		if (++currentSize > array.size() * MAX_LOAD)
			rehash();

		return true;
	}

	bool insertHelper1(HashedObj &&xx)
	{
		int currentPos = findInsertionPos(xx);
		int originPos = myhash(xx);
		int dist = 0; // the distance is legal.

		while (true)
		{
			if ((dist = getDist(currentPos, originPos)) < max_dist)
			{
				array[originPos].setHops(dist);
				array[currentPos].element = std::move(xx);
				array[currentPos].isActive = true;
				break;
			}
			else
			{ // do the rearrange.
				int posStart;
				int offset = -1;
				for (posStart = advanceDist(currentPos, 1 - max_dist);
					posStart != currentPos; posStart = advanceDist(posStart, 1))
				{
					// check that the element is evitable.

					if ((offset = isEvitable(posStart, currentPos)) != -1)
					{
						// evitable the elements.
						evitElement(posStart, offset, getDist(currentPos, posStart));
						break;
					}
				}

				if (posStart == currentPos) // fail to evit any element.
				{
					rehash();
					currentPos = findInsertionPos(xx);
					originPos = myhash(xx);
				}
				else
				{
					currentPos = posStart + offset;
				}
			}
		}

		if (++currentSize > array.size() * MAX_LOAD)
			rehash();

		return true;
	}

	int isEvitable(int originPos, int newPos)
	{
		int distance = getDist(newPos, originPos);
		for (int i = 0; i <= distance; ++i)
			if (array[originPos].getHops(i))
				return i;
		return -1;
	}

	void evitElement(int originPos, int oldOffset, int newOffset)
	{
		int posOld = advanceDist(originPos, oldOffset);
		int posNew = advanceDist(originPos, newOffset);
		std::swap(array[posOld].element, array[posNew].element);
		array[posOld].isActive = false;
		array[posNew].isActive = true;
		array[originPos].clearHops(oldOffset);
		array[originPos].setHops(newOffset);
	}

	inline int getDist(int newPos, int origPos) const
	{
		return (newPos + array.size() - origPos) % array.size();
	}

	inline int advanceDist(int currentPos, int advance) const
	{
		return (currentPos + array.size() + advance) % array.size();
	}

	/**
	* Rehashing for separate chaining hash table.
	*/
	void rehash()
	{
		std::vector<HashEntry> oldArray(nextPrime(array.size() * 2));

		std::swap(oldArray, array);
		// Create new double-sized, empty table
		makeEmpty();

		currentSize = 0;
		for (auto &entry : oldArray)
			if (entry.isActive)
			{
				insert(std::move(entry.element));
			}
	}
};

#endif