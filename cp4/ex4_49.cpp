/*
 * Exercise 4.49
 * Author: sesiria  2018
 * implementation of threaded-tree
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
    bool enablePrevious;
    bool enableNext;

    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, bool bPrev = false, bool bNext = false)
        : element{theElement}, left{lt}, right{rt}, enablePrevious{bPrev}, enableNext{bNext}
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
    if (!node->enablePrevious)
        printTree(node->left);
    std::cout << node->element << " ";
    if (!node->enableNext)
        printTree(node->right);
}

/**
 * Internal method to insert into a subtree.
 * threaded tree insertion routine.
 */
template <typename Comparable>
void insert(const Comparable &x, BinaryNode<Comparable> *&t, BinaryNode<Comparable> *prev, BinaryNode<Comparable> *next)
{
    if (t == nullptr)
        t = new BinaryNode<Comparable>{x, prev, next, (prev) ? true : false, (next) ? true : false};
    else if (x < t->element)
    {
        if (t->enablePrevious)
        {
            t->enablePrevious = false;
            t->left = nullptr; // disable prev thread link for insertion.
        }
        insert(x, t->left, prev, t);
    }
    else if (t->element < x)
    {
        if (t->enableNext)
        {
            t->enableNext = false;
            t->right = nullptr; // disable prev thread link for insertion.
        }
        insert(x, t->right, t, next);
    }
    else
        ; // Duplicate; do nothiing
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
    insert<Comparable>(x, t, nullptr, nullptr);
}

template <typename Comparable>
BinaryNode<Comparable> *findMin(BinaryNode<Comparable> *t)
{
    if (t != nullptr)
        while (t->left != nullptr && t->enablePrevious == false)
            t = t->left;
    return t;
}

template <typename Comparable>
BinaryNode<Comparable> *findMax(BinaryNode<Comparable> *t)
{
    if (t != nullptr)
        while (t->right != nullptr && t->enableNext == false)
            t = t->right;
    return t;
}


template <typename Comparable>
void remove(const Comparable &x, BinaryNode<Comparable> *&t)
{
    if (t == nullptr)
        return; // item not found; do nothing
    if (x < t->element)
        return remove(x, t->left);
    else if (t->element < x)
        return remove(x, t->right);
    else if (t->left != nullptr && t->enablePrevious == false && t->enableNext == false && t->right != nullptr) // two children
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else // one children or none children
    {
        BinaryNode<Comparable> *oldNode = t;

        // relink the linklist if possible.
        if(t->left && t->enablePrevious) // get previous.
        {
            BinaryNode<Comparable> *prev = t->left;
            if(prev->enableNext)
                prev->right = (t->enableNext) ? t->right : nullptr;
        }

        if(t->right && t->enableNext) // get next
        {
            BinaryNode<Comparable> *next = t->right;
            if(next->enablePrevious)
            next->left = (t->enablePrevious) ? t->left : nullptr;
        }
        //t->prev->next = t->next;
        //t->next->prev = t->prev;
        // relink binarytree
        t = (t->left != nullptr && t->enablePrevious == false) ? t->left : (t->right != nullptr && t->enableNext == false) ? t->right : nullptr;
        delete oldNode;
    }
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

int main(int argc, char **argv)
{
    BinaryNode<int> *root = nullptr;
    generateRandomBST(root, 100);

    printTree(root);
    std::cout << std::endl;
    remove(21, root);
    remove(15, root);
    remove(33, root);
    printTree(root);
    std::cout << std::endl;
    return 0;
}
