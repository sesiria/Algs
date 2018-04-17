/*
* Exercise 6.10a
* Author: sesiria  2018
* print all element less than k from an binary heap.
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

template <typename Comparable>
class BinaryHeap{
  public:
    explicit BinaryHeap(int capacity = 100)
     : currentSize{0}, array(capacity < 100 ? 100 : capacity)
    {

    }

    explicit BinaryHeap(const std::vector<Comparable> &items)
     : array{items.size() + 10}, currentSize{items.size()}
    {
        for (int i = 0; i < items.size(); ++i)
            array[i + 1] = items[i];
        buildHeap();
    }

    bool isEmpty() const
    {
        return currentSize == 0;
    }

    const Comparable &findMin() const
    {
        if(isEmpty())
            std::__throw_underflow_error(
                "Try to delete element from an empty heap");

        return array[1];
    }

    /**
     * Insert item x, allowing duplicates.
     * time complexity O(logN)
     */ 
    void insert(const Comparable &x)
    {
        if(currentSize == array.size() - 1)
            array.resize(array.size() * 2);

        // Percolate up
        int hole = ++currentSize;
        Comparable copy = x;
        array[0] = std::move(copy);
        for (; x < array[hole / 2]; hole /= 2)
            array[hole] = std::move(array[hole / 2]);
        array[hole] = std::move(array[0]);
    }

    /**
     * Insert item x, allowing duplicates.
     * time complexity O(logN)
     */     
    void insert(Comparable &&x)
    {
        if(currentSize == array.size() - 1)
            array.resize(array.size() * 2);

        // Percolate up
        int hole = ++currentSize;
        for (; x < array[hole / 2] && hole != 1; hole /= 2)
            array[hole] = std::move(array[hole / 2]);
        array[hole] = std::move(x);
    }

    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */ 
    void deleteMin()
    {
        if(isEmpty())
            std::__throw_underflow_error(
                "Try to delete element from an empty heap");

        array[1] = std::move(array[currentSize--]);
        percolateDown(1);
    }

    /**
     * Remove the minimum item and place it in miniItem.
     * Throw UnderflowException if empty.
     */ 
    void deleteMin(Comparable &minItem)
    {
        if(isEmpty())
            std::__throw_underflow_error(
                "Try to delete element from an empty heap");

        minItem = std::move(array[1]);
        array[1] = std::move(array[currentSize--]);
        percolateDown(1);
    }

    void makeEmpty();

    void printElements(const Comparable &x);

  private:
    int currentSize;                    // Number of elements in heap
    std::vector<Comparable> array;      // The heap array


    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */ 
    void buildHeap()
    {
        for (int i = currentSize / 2; i > 0; --i)
            percolateDown(i);
    }

    /**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */ 
    void percolateDown(int hole)
    {
        int child;
        Comparable tmp = std::move(array[hole]);

        while (hole * 2 <= currentSize)
        {
            child = hole * 2;
            // whether the current node have the left child.
            if(child != currentSize && array[child + 1] < array[child])
                ++child;
            
            if(array[child] < tmp)
                array[hole] = std::move(array[child]);
            else
                break;

            hole = child;
        }
        array[hole] = std::move(tmp);
    }
};


/**
 * Print all of the elements less then X from a binary heap.
 * time complexity O(K)
 */ 
template <typename Comparable>
void BinaryHeap<Comparable>::printElements(const Comparable &x)
{
    if(isEmpty())
        return;
    size_t pos = 1;
    std::stack<size_t> stackPos;
    if(array[pos] < x)
        stackPos.push(pos);
    int count = 0;
    while(!stackPos.empty()) {
        pos = stackPos.top();
        stackPos.pop();
        std::cout << array[pos] << " ";
        if(pos * 2 + 1 <= currentSize && array[pos * 2 + 1] < x) // right child
            stackPos.push(pos * 2 + 1);
        if(pos * 2 <= currentSize && array[pos * 2] < x) // left child
            stackPos.push(pos * 2);
        ++count;
    }
    std::cout << "iterator " << count << " times" << std::endl;
}

int main()
{
    BinaryHeap<int> heap;
    for (int i = 0; i < 1000; ++i)
        heap.insert(i);
    heap.printElements(30);
    return 0;
}