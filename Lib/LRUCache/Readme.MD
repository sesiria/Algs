## The Least Recent Used Memory Cache Implementation
* support C++17 and thread-safe
* support get(), put(), size(), capacity()
* the value should be a C++ smart pointer container.

the test case

~~~~~ c
#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stdint.h>
#include <memory>
#include "LRUCache.hpp"

using namespace std;

typedef LRUCache<string, shared_ptr<uint64_t>> CacheType;

void job(void * arg) {
	do {
		// do some jobs
		int tmp = 1;
		for (int i = 0; i < 1000000; i++) {
			tmp <<= 2;
			tmp = (~tmp + i) * i;
		}
	} while (0);

}

void thread_write(void * arg) {
	CacheType* cache = (CacheType*)arg;

	unsigned i = 0;
	while (true) {
		cache->put(to_string(i), make_shared<uint64_t>(i));
		if (i != 0 && i % 1000000 == 0) {
			cout << "In thread: " << std::this_thread::get_id() << " ";
			cout << "the current size of the cache is: "<< cache->size() << endl;
			cache->clear();
			cout << "clear data" << endl;
		}
		i++;
	}
}

void thread_read(void* arg) {
	CacheType* cache = (CacheType*)arg;

	unsigned i = 0;
	unsigned cnt = 0;
	while (true) {
		shared_ptr<uint64_t> ptr;
		if (cache->get(to_string(i), ptr)) {
			/*cnt++;
			if(cnt % 1000 == 0)*/
			cout << "In thread: " << std::this_thread::get_id() << " ";
			cout << "Found cache data: " << *ptr << endl;
			
		}
		job(nullptr);
		i = i * 2 + (++i);
	}
}

int main()
{
	CacheType memcache(500000);
	vector<thread> vec;
	for (int i = 0; i < 6; i++) {
		
		vec.push_back(thread(thread_read, &memcache));
	}
	vec.push_back(thread(thread_write, &memcache));
	vec.push_back(thread(thread_write, &memcache));
	

	for (auto& x : vec) {
		x.join();
	}

	return 0;
}
~~~~~