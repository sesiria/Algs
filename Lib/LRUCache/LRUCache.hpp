/**
* The Least Recent Used Memory Cache Data Structure 
* FileName: LRUCache.hpp
* Author: Sesiria  2021-05-11
* Support concurrency and thread-safe by STL mutex.
*/

#ifndef LRU_CACHE_HEADER
#define LRU_CACHE_HEADER
#include <string>
#include <algorithm>
#include <unordered_map>
#include <shared_mutex>

#define DEFAULT_CACHE_CAPACITY	1024	// the default size of the LRU Cache

// Least Recent Used Memory Cache Data structure.
// K for the type of Key, the Key should support the hash function.
// T for the type of data type , T must be shared_pointer to support the thread-safe
template <typename K, typename T>
class LRUCache
{
private:
	struct Linklist
	{
		K _key;
		T _data;
		Linklist *next;
		Linklist *prev;
		// the default constructor.
		Linklist() :next(nullptr), prev(nullptr) {}

		Linklist(K key, T data) 
			: _key(key), _data(data), next(nullptr), prev(nullptr) {}
	};

	std::unordered_map<K, Linklist *> table;	// hashtable to store the buffer by key, value
	std::shared_mutex _mtx;	// mutex object for thread-safe
	Linklist *head;		// virtual header.
	Linklist *tail;		// virtual tailer node.
	int theCapacity;	// the number of elements stored in the hashtable

	// private method.
	void removeFromList(Linklist *node)
	{
		// cut the node from list
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	void insertToHeader(Linklist *node)
	{
		node->next = head->next;
		node->next->prev = node;

		head->next = node;
		node->prev = head;
	}

public:
	LRUCache()
		:theCapacity(DEFAULT_CACHE_CAPACITY)
	{
		head = new Linklist();
		tail = new Linklist();
		head->next = tail;
		tail->prev = head;
	}
	LRUCache(int capacity)
	{
		theCapacity = capacity;
		head = new Linklist();
		tail = new Linklist();
		head->next = tail;
		tail->prev = head;
	}

	~LRUCache()
	{
		clear();
		if(head)
			delete head;
		if(tail)
			delete tail;
	}

	// thread safe get buffer data from key
	bool get(K key, T& val)
	{
		std::unique_lock<std::shared_mutex> lock(_mtx);
		auto iter = table.find(key);
		if (iter == table.end())
			return false;
		else
		{
			Linklist *node = iter->second;
			removeFromList(node);
			insertToHeader(node);
			val = node->_data;
			return true;
		}
	}

	// thread safe put data into buffer.
	void put(K key, T value)
	{
		std::unique_lock<std::shared_mutex> lock(_mtx);
		auto iter = table.find(key);
		// the key is already existed.
		if (iter != table.end())
		{
			Linklist *node = iter->second;
			// allocate the new node and delete the old node
			Linklist *newNode = new Linklist(key, value);
			// update the new node into hashtable.
			iter->second = newNode; 
			// insert the newNode into the linklist
			insertToHeader(newNode);

			// cut the old node from linklist and delete it
			removeFromList(node);
			delete node;
		}
		else
		{
			// the LRU cache is full, we remove the last element.
			if (table.size() == theCapacity)
			{
				Linklist *node = tail->prev;
				table.erase(node->_key);
				removeFromList(node);
				delete node;
			}

			Linklist *newNode = new Linklist(key, value);
			insertToHeader(newNode);
			table.insert(std::make_pair(key, newNode));
		}
	}

	// clear all of the data in the cache
	void clear()
	{
		std::unique_lock<std::shared_mutex> lock(_mtx);
		// clear the hashtable
		// clear the linklist
		Linklist* p = head->next,  *q;
		while (p && p != tail) {
			q = p->next;
			delete p;
			p = q;
		}
		// relink the head and tail
		head->next = tail;
		tail->prev = head;
		table.clear();
	}

	// return the current number of elements in the cache
	size_t size() {
		std::shared_lock<std::shared_mutex> lock(_mtx);
		return table.size();
	}

	// return the capacity number of the cache
	size_t capacity() {
		std::shared_lock<std::shared_mutex> lock(_mtx);
		return theCapacity;
	}

};

#endif