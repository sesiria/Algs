// Author sesiria 2019
// thread safe priority queue implementation base on the
// STL priority_queue,  shared_mutex(C++17) and condition_variable
// Reference C++ Concurrency in Action by Anthony Williams,2nd.
// must be complied by C++17 or later.
#include <queue>
#include <vector>
#include <algorithm>
#include <condition_variable>
// Important: only support by C++17 or later
#include <shared_mutex>         // support read/write lock

template<typename _Tp, typename _Sequence = std::vector<_Tp>,
	   typename _Compare  = std::less<typename _Sequence::value_type> >
class threadsafe_priority_queue
{
private:
    std::priority_queue<_Tp, _Sequence, _Compare> data_heap;
    mutable std::shared_mutex mut;
    std::condition_variable data_cond;
public:
    threadsafe_priority_queue()
    {}
    threadsafe_priority_queue(const threadsafe_priority_queue & other) {
        std::lock_guard<std::shared_mutex> lk(other.mut);
        data_heap = other.data_heap;
    }

    void push(_Tp &&new_value) {
        std::lock_guard<std::shared_mutex> lk(mut);
        data_heap.push(std::move(new_value));
    }

    void push(const _Tp &new_value) {
        std::lock_guard<std::shared_mutex> lk(mut);
        data_heap.push(new_value);
    }

    void wait_and_pop(_Tp & value) {
        std::unique_lock<std::shared_mutex> lk(mut);
        data_cond.wait(lk, [this] { return !data_heap.empty(); });
        value = data_heap.top();
        data_heap.pop();
    }

    void wait_and_pop() {
        std::unique_lock<std::shared_mutex> lk(mut);
        data_cond.wait(lk, [this] { return !data_heap.empty(); });
        data_heap.pop();
    }

    bool try_pop(_Tp& value) {
        std::lock_guard<std::shared_mutex> lk(mut);
        if(data_heap.empty())
            return false;
        value = data_heap.top();
        data_heap.pop();
        return true;
    }

    bool try_pop() {
        std::lock_guard<std::shared_mutex> lk(mut);
        if(data_heap.empty())
            return false;
        data_heap.pop();
        return true;
    }

    // for read heap use the shared_lock for reading
    const _Tp & top() const {
        std::shared_lock<std::shared_mutex> lk(mut);
        return data_heap.top();
    }

    void push_and_pop(_Tp && new_value) {
        std::lock_guard<std::shared_mutex> lk(mut);
        data_heap.push(std::move(new_value));
        data_heap.pop();
    }

    void push_and_pop(const _Tp & new_value) {
        std::lock_guard<std::shared_mutex> lk(mut);
        data_heap.push(new_value);
        data_heap.pop();
    }

    // for read heap use the shared_lock for reading
    bool empty() const {
        std::shared_lock<std::shared_mutex> lk(mut);
        return data_heap.empty();
    }
};