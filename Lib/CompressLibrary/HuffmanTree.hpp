/**
* The Huffman Tree algorithm implementation
* FileName: HuffmanTree.hpp
* Author: Sesiria  2021-05-22
* Not support concurrency!
*/

#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <iostream>
#include <queue>
#include <vector>

// the definition of the huffmanTreeNode struct
template <typename T>
struct HuffmanTreeNode
{
	HuffmanTreeNode(const T&weight, 
		HuffmanTreeNode * pLeft = nullptr,
		HuffmanTreeNode * pRight = nullptr,
		HuffmanTreeNode * pParent = nullptr)
	:_pLeft(pLeft),
	 _pRight(pRight),
	 _pParent(pParent),
	 _weight(weight)
	{

	}

	HuffmanTreeNode * _pLeft;
	HuffmanTreeNode * _pRight;
	HuffmanTreeNode* _pParent;
	T _weight;
};

// the definition of the HuffmanTree Encoding class implementation
template<typename T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T>* pNode;
public:
	HuffmanTree() :_pRoot(nullptr) {}

	~HuffmanTree() {
		_destory(_pRoot);
	}

	HuffmanTree(T* array, size_t size, const T& invalid) {
		_createHuffmanTree(array, size, invalid);
	}

	pNode getRoot() {
		return _pRoot;
	}

private:
	// create the HuffmanTree
	void _createHuffmanTree(T* array, size_t size, const T& invalid) {
		struct PtrNodeCompare {
			// override the operator ()
			bool operator()(pNode lhs, pNode rhs) {
				return lhs->_weight < rhs->_weight;
			}
		};

		std::priority_queue<pNode, std::vector<pNode>, PtrNodeCompare> hp; // define the minHeap

		for (size_t i = 0; i < size; ++i) {
			if (array[i] != invalid) {
				hp.push(new HuffmanTreeNode<T>(array[i])); // push into the minHeap
			}
		}

		if (hp.empty())
			_pRoot = nullptr;

		// build the huffmanTree

		while (hp.size() > 1) {
			pNode pLeft = hp.top();
			hp.pop();
			pNode pRight = hp.top();
			hp.pop();
			pNode pParent = new HuffmanTreeNode<T>{ pLeft->_weight + pRight->_weight,
				pLeft, pRight };
			pLeft->_pParent = pRight->_pParent = pParent;
			hp.push(pParent);
		}
		_pRoot = hp.top();	// the left only one node is the root of the tree
	}

	void _destory(pNode& pRoot) {
		if (pRoot) {
			_destory(pRoot->_pLeft);
			_destory(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}
public:
	pNode _pRoot;
};

#endif
