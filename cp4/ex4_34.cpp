/*
 * Exercise 4.33
 * Author: sesiria  2018
 * remove the leaves from an binary tree.
 * time complexity O(N)
 */

#include "../Lib/randomize.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <time.h>
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
 * generateRandomTree base on recursive bound.
 * dive-and-conquer
 * time complexity O(NlogN)
 */
BinaryNode<int> *genRandomTree(int lower, int upper)
{
    BinaryNode<int> *t = nullptr;
    int randomValue;

    if (lower <= upper)
    {
        t = new BinaryNode<int>{(randomValue = randInt(lower, upper)),
                                genRandomTree(lower, randomValue - 1),
                                genRandomTree(randomValue + 1, upper)};
    }

    return t;
}

/**
 * generateRandomBST base on recursive bound.
 * time complexity O(N)
 */
template <typename Comparable>
void generateRandomBST2(BinaryNode<Comparable> *&t, int nSize)
{
    t = genRandomTree(0, nSize);
}

typedef void (*func)(BinaryNode<int> *&t, int);
void testGenerate(func fun, BinaryNode<int> *&t, int nSize)
{
    clock_t start = clock();
    fun(t, nSize);
    clock_t end = clock();
    printf("Time cost is %f.\n", (end - start) / (float)(CLOCKS_PER_SEC));
    makeEmpty(t);
}

int main(int argc, char **argv)
{
    BinaryNode<int> *root = nullptr;
    generateRandomBST(root, 10);
    printTree(root);
    std::cout << std::endl;

    BinaryNode<int> *root2 = nullptr;
    generateRandomBST(root2, 10);
    printTree(root2);
    std::cout << std::endl;

    BinaryNode<int> *root3 = nullptr;
    generateRandomBST2(root3, 10);
    printTree(root2);
    std::cout << std::endl;

    testGenerate(generateRandomBST, root, 200000);
    testGenerate(generateRandomBST2, root, 200000);
    return 0;
}
