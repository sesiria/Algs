#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H


#include <algorithm>
#include <vector>

template <typename Comparable>
class BinaryHeap{
  public:
    explicit BinaryHeap(int capacity = 100);
    explicit BinaryHeap(const std::vector<Comparable> &items);

    bool isEmpty() const
    {
        return currentSize == 0;
    }
    const Comparable &findMin() const;

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
 
  private:
    int currentSize;                    // Number of elements in heap
    std::vector<Comparable> array;      // The heap array

    void buildHeap();

    /**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */ 
    void percolateDown(int hole)
    {
        int child;
        Comparable tmp = std::move[array[hole]];

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

#endif