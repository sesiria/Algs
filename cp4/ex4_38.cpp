/*
 * Exercise 4.38
 * Author: sesiria  2018
 * calculate the coordinate of XY for the node of binary search tree.
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
    int x_pos;
    int y_pos;

    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, int x = 0, int y = 0)
        : element{theElement}, left{lt}, right{rt}, x_pos{x}, y_pos{y}
    {
    }

    BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt, int x = 0, int y = 0)
        : element{std::move(theElement)}, left{lt}, right{rt}, x_pos{x}, y_pos{y}
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
    printf("with coordinate (%d, %d).\n", node->x_pos, node->y_pos);
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
 * update all node's x coordinate.
 * time complexity O(N).
 */ 
template <typename Comparable>
void calculateCoordinateX(BinaryNode<Comparable> *t, int & lastposX, int distance)
{
    if(t == nullptr)
        return;
    calculateCoordinateX(t->left, lastposX, distance);
    t->x_pos = lastposX;
    lastposX += distance;
    calculateCoordinateX(t->right, lastposX, distance);
}

/**
 * update all node's x coordinate.
 */ 
template <typename Comparable>
void calculateCoordinateX(BinaryNode<Comparable> *t, int distance = 10)
{
    int initPosX = distance;
    calculateCoordinateX(t, initPosX, distance);
}


/**
 * update all node's y coordinate.
 */ 
template <typename Comparable>
void calculateCoordinateY(BinaryNode<Comparable> *t, int initposY, int depth, int distance)
{
    if(t == nullptr)
        return;
    calculateCoordinateY(t->left, initposY, depth + 1, distance);
    t->y_pos = initposY + depth * distance;
    calculateCoordinateY(t->right, initposY, depth + 1, distance);
}

/**
 * update all node's x coordinate.
 */ 
template <typename Comparable>
void calculateCoordinateY(BinaryNode<Comparable> *t, int distance = 15)
{
    int initposY = distance;
    calculateCoordinateY(t, initposY, 0, distance);
}

int main(int argc, char **argv)
{
    BinaryNode<int> *root = nullptr;
    generateRandomBST(root, 20);
    calculateCoordinateX(root);
    calculateCoordinateY(root);
    printTree(root);
    return 0;
}
