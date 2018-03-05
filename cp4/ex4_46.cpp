/*
 * Exercise 4.45
 * Author: sesiria  2018
 * check whether two binary tree are similar.
 */

#include "../Lib/Queue.h"
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

/**
 * inorder-traversal
 */
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
 * level-order-traversal of binary search tree
 * time complexity O(N)
 * space complexity O(N)
 * base on the data structure queue
 */
template <typename Comparable>
void printLevelNodes1(BinaryNode<Comparable> *node)
{
    Queue<BinaryNode<Comparable> *> queue;
    queue.enqueue(node);
    printLevelQueue(queue);
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
 * isomorphic two binary tree.
 * time complexity O(N)
 */ 
template <typename Comparable>
bool isomorphicBinaryTree(BinaryNode<Comparable> *t1, BinaryNode<Comparable> *t2)
{
    if(t1 == nullptr && t2 == nullptr)
        return true;
    else if(t1 == nullptr || t2 == nullptr)
        return false; 

    if(t1->element != t2->elemnt)
        return false;

    return isomorphicBinaryTree(t1->left, t2->right) && isomorphicBinaryTree(t1->right, t2->left);
}

int main(int argc, char **argv)
{
    BinaryNode<int> *root = nullptr;
    generateRandomBST(root, 100);

    return 0;
}
