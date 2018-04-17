
/**
* Author: sesiria  2018
* A implementation for Min-Max Heap
* min-max heap implementation support the following interface
* 1) insert for O(logN)
* 2) deleteMin for O(logN)
* 3) deleteMax for O(logN)
* 4) buildheap for O(N)
*/
#ifndef MINMAX_HEAP_H
#define MINMAX_HEAP_H

#include <algorithm>
#include <vector>
#include <cassert>
#include <stdexcept>

template <typename Comparable>
class MinMaxHeap
{
public:
	explicit MinMaxHeap(int capacity = 100)
		: currentSize{ 0 }, array(capacity < 100 ? 100 : capacity)
	{
	}

	explicit MinMaxHeap(const std::vector<Comparable> &items)
		: currentSize( items.size() ), array(items.size() + 10)
	{
		for (size_t i = 0; i < items.size(); ++i)
			array[i + 1] = items[i];
		buildHeap();
	}

	bool isEmpty() const
	{
		return currentSize == 0;
	}

	const Comparable &findMin() const
	{
		if (isEmpty())
			throw std::runtime_error("Try to delete element from an empty heap");

		return array[1];
	}

	const Comparable &findMax() const
	{
		if (isEmpty())
			throw std::runtime_error("Try to delete element from an empty heap");

		if (currentSize == 1)
			return array[1];
		else if (currentSize == 2)
			return array[2];
		else
			return array[2] > array[3] ? array[2] : array[3];
	}



	/**
	* Insert item x, allowing duplicates.
	* time complexity O(logN)
	*/
	void insert(const Comparable &x)
	{
		Comparable copy = x;
		insert(std::move(copy));
	}

	/**
	* Insert item x, allowing duplicates.
	* time complexity O(logN)
	*/
	void insert(Comparable &&x)
	{
		if (currentSize == array.size() - 1)
			array.resize(array.size() * 2);

		// Percolate up or down
		int hole = ++currentSize;
		array[hole] = std::move(x);
		if (getDepth(hole) % 2 == 0) // at the even depth
			percolateEven(hole);
		else
			percolateOdd(hole);
	}

	/**
	* Remove the minimum item.
	* Throws UnderflowException if empty.
	*/
	void deleteMin()
	{
		Comparable tmp{};
		deleteMin(tmp);
	}

	/**
	* Remove the minimum item and place it in miniItem.
	* Throw UnderflowException if empty.
	*/
	void deleteMin(Comparable &minItem)
	{
		if (isEmpty())
			throw std::runtime_error("Try to delete element from an empty heap");

		minItem = std::move(array[1]);
		array[1] = std::move(array[currentSize--]);
		percolateEven(1);
	}

	/**
	* Remove the maximum item.
	* Throws UnderflowException if empty.
	*/
	void deleteMax()
	{
		Comparable tmp{};
		deleteMax(tmp);
	}

	void deleteMax(Comparable &maxItem)
	{
		if (isEmpty())
			throw std::runtime_error("Try to delete element from an empty heap");

		int maxPos = findMaxPosition();
		maxItem = std::move(array[maxPos]);
		if (maxPos != currentSize) {
			array[maxPos] = std::move(array[currentSize--]);
			if (currentSize > 1)
				percolateOdd(maxPos);
		}
		else
			--currentSize;
	}

	void makeEmpty();

private:
	int currentSize;               // Number of elements in heap
	std::vector<Comparable> array; // The heap array

	/**
	* Establish heap order property from an arbitrary
	* arrangement of items. Runs in linear time.
	*/
	void buildHeap()
	{
		// level order traversal
		if (getDepth(currentSize) % 2 == 0) {
			for (int l = 0; l <= getDepth(currentSize); l += 2)
				traverseLevel(l);
			for (int l = getDepth(currentSize) - 1; l > 0; l -= 2)
				traverseLevel(l);
		}
		else {
			for (int l = 0; l < getDepth(currentSize); l += 2)
				traverseLevel(l);
			for (int l = getDepth(currentSize); l > 0; l -= 2)
				traverseLevel(l);
		}
	}

	/**
	* percolate down from the even level.
	*/
	int percolateDownEven(int hole)
	{
		assert(getDepth(hole) % 2 == 0); // at the even depth
		int child;
		Comparable tmp = std::move(array[hole]);

		while (hole * 4 <= currentSize)
		{
			child = hole * 4;

			// choose the minChild from the 4 child is available.
			int minChild = child;
			++child;
			for (int id = 1; id != 4 && child <= currentSize;
				++id, ++child) {
				if (array[child] < array[minChild])
					minChild = child;
			}

			child = minChild;
			if (array[child] < tmp)
				array[hole] = std::move(array[child]);
			else
				break;
			hole = child;
		}
		array[hole] = std::move(tmp);
		return hole;
	}

	/**
	* percolate down from the odd level.
	*/
	int percolateDownOdd(int hole)
	{
		assert(getDepth(hole) % 2 == 1); // at the odd depth

		int child;
		Comparable tmp = std::move(array[hole]);

		while (hole * 4 <= currentSize)
		{
			child = hole * 4;

			// choose the maxChild from the 4 child is available.
			int maxChild = child;
			++child;
			for (int id = 1; id != 4 && child <= currentSize;
				++id, ++child) {
				if (array[child] > array[maxChild])
					maxChild = child;
			}
			child = maxChild;
			if (array[child] > tmp)
				array[hole] = std::move(array[child]);
			else
				break;
			hole = child;
		}
		array[hole] = std::move(tmp);
		return hole;
	}

	/**
	* percolate up from the even level.
	*/
	int percolateUpEven(int hole)
	{
		assert(getDepth(hole) % 2 == 0); // at the even depth

		Comparable tmp = std::move(array[hole]);
		for (; hole >= 4 && tmp < array[hole / 4]; hole /= 4)
		{
			array[hole] = std::move(array[hole / 4]);
		}

		array[hole] = std::move(tmp);
		return hole;
	}

	/**
	* percolate up from the odd level.
	*/
	int percolateUpOdd(int hole)
	{
		assert(getDepth(hole) % 2 == 1); // at the odd depth

		Comparable tmp = std::move(array[hole]);
		for (; hole >= 4 && tmp > array[hole / 4]; hole /= 4)
		{
			array[hole] = std::move(array[hole / 4]);
		}

		array[hole] = std::move(tmp);
		return hole;
	}

	int getDepth(int pos)
	{
		int nDepth = 0;
		while (pos >= 2)
		{
			pos /= 2;
			nDepth++;
		}
		return nDepth;
	}

	int power(int x, int n)
	{
		if (n == 0)
			return 1;
		if (n == 1)
			return x;
		if (n % 2 == 0)
			return power(x * x, n / 2);
		else
			return x * power(x * x, n / 2);
	}

	int findMaxPosition() const
	{
		if (isEmpty())
			throw std::runtime_error("Try to delete element from an empty heap");

		if (currentSize == 1)
			return 1;
		else if (currentSize == 2)
			return 2;
		else
			return array[2] > array[3] ? 2 : 3;
	}

	void percolateEven(int hole)
	{
		// try move to low position.
		// if it success, return.
		if (percolateUpEven(hole) != hole)
			return;
		
		// try move to large position.
		hole = percolateDownEven(hole);

		// adjust even and odd level.
		// if it is a complete tree.
		if (hole * 2 <= currentSize) {
			// choose minChild.
			int child = hole * 2;
			if (child != currentSize && array[child + 1] < array[child])
				++child;
			if (array[child] < array[hole]) {
				std::swap(array[hole], array[child]); // move to child with odd-level.
				percolateUpOdd(child);
			}
		} // if it is not a complete tree.
		if (hole >= 2 && array[hole] > array[hole / 2]) { 
			std::swap(array[hole], array[hole / 2]); // move to parent with odd-level
			hole /= 2;
			percolateUpOdd(hole);
		}
	}

	void percolateOdd(int hole)
	{
		// try move to large position.
		if (percolateUpOdd(hole) != hole)
			return;

		// try move to low position.
		// if it is a complete tree.
		hole = percolateDownOdd(hole);

		// adjust even and odd level.
		if (hole * 2 <= currentSize) {
			if (hole * 2 <= currentSize) {
				// choose maxChild.
				int child = hole * 2;
				if (child != currentSize && array[child + 1] > array[child])
					++child;

				if (array[child] > array[hole]) {
					std::swap(array[hole], array[child]);
					percolateUpEven(child);
				}
			}
		} // if it is not a complete tree.
		if (currentSize > 3 && hole >= 2 && array[hole] < array[hole / 2])
		{
			std::swap(array[hole], array[hole / 2]);
			hole /= 2;
			percolateUpEven(hole);
			return;
		}
	}

	void traverseLevel(int level)
	{
		bool isEven = (level % 2 == 0);
		for (int start = power(2, level), end = 2 * start;
			start != end && start <= currentSize; ++start) {
			if (isEven)
				percolateEven(start);
			else
				percolateOdd(start);
		}		
	}
};

#endif