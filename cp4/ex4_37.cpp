/*
 * Exercise 4.37
 * Author: sesiria  2018
 * generate random binary search tree
 * time complexity O(NlogN)
 */

#include "../Lib/randomize.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

template <typename Comparable>
struct BinaryNode
{
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
        : element{theElement}, left{lt}, right{rt}
    {
    }

    BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
        : element{std::move(theElement)}, left{lt}, right{rt}
    {
    }
};

template <typename Comparable>
void printTree(BinaryNode<Comparable> *node)
{
    if (node == nullptr)
        return;
    printTree(node->left);
    std::cout << node->element << " ";
    printTree(node->right);
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template <typename Comparable>
void insert(const Comparable &x, BinaryNode<Comparable> *&t)
{
    if (t == nullptr)
        t = new BinaryNode<Comparable>{x, nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ; // Duplicate; do nothiing
}

template <typename Comparable>
void makeEmpty(BinaryNode<Comparable> *&t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

/**
 * Fisher-Yaster/Donald.Knuth random shuffle algorithm
 * time complexity O(N)
 */
void shuffleVector(std::vector<int> &ar)
{
    for (int i = 1; i < ar.size(); ++i)
    {
        std::swap(ar[i], ar[randInt(0, i)]);
    }
}

/**
 * generateRandomBST base on the Fisher-Yaster/Donald.Knuth random shuffle algorithm
 * time complexity O(NlogN)
 * space complexity O(N)
 */
template <typename Comparable>
void generateRandomBST(BinaryNode<Comparable> *&t, int nSize)
{
    std::vector<Comparable> vec;
    for (int i = 1; i <= nSize; ++i) // O(N)
        vec.push_back(i);

    shuffleVector(vec); // O(N)

    for (int i = 0; i < vec.size(); ++i) // insert node O(NlogN)
        insert(vec[i], t);
}

/**
 * print all of the key within the range key1 < x < key2.
 * assume key1 <= key2.
 * time complexity O(k + logN) k is the number of key printed.
 */ 
template<typename Comparable>
void printKeys(BinaryNode<Comparable> *t, const Comparable & key1, const Comparable & key2)
{
    if(t == nullptr)
        return;
    if(key1 < t->element)
        printKeys(t->left, key1,  key2);
    if(key1 <= t->element && t->element <= key2)
        std::cout << t->element << " ";
    if(t->element < key2)
        printKeys(t->right, key1, key2);
}


int main(int argc, char **argv)
{
    BinaryNode<int> *root = nullptr;
    generateRandomBST(root, 100);
    printKeys(root, 25, 37);
    std::cout << std::endl;

    BinaryNode<int> *root1 = nullptr;
    int a[] = {5, 4, 3, 7, 9, 12, 6, 1, 14, 8};
    for (int i = 0; i < _countof(a); ++i)
        insert(a[i],root1);

    printKeys(root1, 5, 37);
    std::cout << std::endl;

    printKeys(root1, -10, 37);
    std::cout << std::endl;

    printKeys(root1, -1, 5);
    std::cout << std::endl;
    return 0;
}
