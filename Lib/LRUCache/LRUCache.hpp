/**
* The Least Recent Used Memory Cache Data Structure
* FileName: LRUCache.hpp
* Author: Sesiria  2021-05-11
* Support concurrency and thread-safe by STL mutex.
* Requirement: C++17 or later compiler, otherwise you
* should used the boost::shared_mutex to replace the std::shared_mutex.
*/

#ifndef LRU_CACHE_HEADER
#define LRU_CACHE_HEADER
#include <string>
#include <algorithm>
#include <unordered_set>
#include <shared_mutex>

#define DEFAULT_CACHE_CAPACITY	1024	// the default size of the LRU Cache

// Least Recent Used Memory Cache Data structure.
// K for the type of Key, the Key should support the hash function.
// T for the type of data type , T must be shared_pointer to support the thread-safe
template <typename K, typename T>
class LRUCache
{
private:
	// define the double-linklist node in the LRU queue.
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
	
	// define the custom hash function for the hash set container.
	struct link_node_hash {
		size_t operator()(const Linklist* l) const {
			return std::hash<K>()(l->_key);
		}
	};

	// define the custom equal function for the hash set container.
	struct link_node_equal {
		bool operator()(const Linklist* lhs, const Linklist* rhs) const {
			return lhs->_key == rhs->_key;
		}
	};

	// define the hashSet type.
	using hashSetType = std::unordered_set<Linklist *, link_node_hash, link_node_equal> ;
	hashSetType hashSet;	// hashtable to store the buffer by key, value
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
		if (head)
			delete head;
		if (tail)
			delete tail;
	}

	// thread safe get buffer data from key
	bool get(const K &key, T& val)
	{
		std::unique_lock<std::shared_mutex> lock(_mtx);
		auto iter = hashSet.find((Linklist*)&key);
		if (iter == hashSet.end())
			return false;
		else
		{
			Linklist *node = *iter;
			removeFromList(node);
			insertToHeader(node);
			val = node->_data;
			return true;
		}
	}

	// thread safe put data into buffer.
	void put(const K &key, T value)
	{
		std::unique_lock<std::shared_mutex> lock(_mtx);
		// we must used the non-const iterator
		auto iter = hashSet.find((Linklist*)&key);
		// the key is already existed.
		if (iter != hashSet.end())
		{
			Linklist *node = *iter;
			node->_data = value; //replace the old value.
			// move the node from middle to the header.
			removeFromList(node);
			insertToHeader(node);
		}
		else
		{
			// the LRU cache is full, we remove the last element.
			if (hashSet.size() == theCapacity)
			{
				Linklist *node = tail->prev;
				hashSet.erase((Linklist*)&key);
				removeFromList(node);
				delete node;
			}

			Linklist *newNode = new Linklist(key, value);
			insertToHeader(newNode);
			hashSet.insert(newNode);
		}
	}

	// clear all of the data in the cache
	void clear()
	{
		std::unique_lock<std::shared_mutex> lock(_mtx);
		// clear the hashtable
		// clear the linklist
		Linklist* p = head->next, *q;
		while (p && p != tail) {
			q = p->next;
			delete p;
			p = q;
		}
		// relink the head and tail
		head->next = tail;
		tail->prev = head;
		hashSet.clear();
	}

	// return the current number of elements in the cache
	size_t size() {
		std::shared_lock<std::shared_mutex> lock(_mtx);
		return hashSet.size();
	}

	// return the capacity number of the cache
	size_t capacity() {
		std::shared_lock<std::shared_mutex> lock(_mtx);
		return theCapacity;
	}

};

#endif
