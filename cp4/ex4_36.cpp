/*
 * Exercise 4.36
 * Author: sesiria  2018
 * generate full balanced AVLTree
 */

#include "../Lib/randomize.h"
#include <algorithm>
#include <iostream>
#include <ostream>

template <typename Comparable>
struct AvlNode
{
    Comparable element;
    AvlNode *left;
    AvlNode *right;
    int height;

    AvlNode(const Comparable &theElement, AvlNode *lt, AvlNode *rt, int h = 0)
        : element{theElement}, left{lt}, right{rt}, height{h}
    {
    }

    AvlNode(Comparable &&theElement, AvlNode *lt, AvlNode *rt, int h = 0)
        : element{std::move(theElement)}, left{lt}, right{rt}, height{h}
    {
    }
};

template <typename Comparable>
void printTree(AvlNode<Comparable> *node)
{
    if (node == nullptr)
        return;
    printTree(node->left);
    std::cout << node->element << " ";
    printTree(node->right);
}

template <typename Comparable>
void makeEmpty(AvlNode<Comparable> *&t)
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
 * generateAVLTree with height h and fewest node.
 * time complexity is O(2^N)
 * it is a fibonacci number.
 */
AvlNode<int> *generateAVLSubTree(int height, int &last)
{
    AvlNode<int> *t = nullptr;
    if (height >= 0)
    {
        t = new AvlNode<int>{0, nullptr, nullptr, height};
        t->left = generateAVLSubTree(height - 1, last);
        t->element = last++;
        t->right = generateAVLSubTree(height - 1, last);
    }
    return t;
}

/**
 * generateFullBalanceTree with key 1
 */
template <typename Comparable>
void generateFullBST(AvlNode<Comparable> *&t, int height)
{
    int initkey = 1;
    t = generateAVLSubTree(height, initkey);
}


int main(int argc, char **argv)
{
    AvlNode<int> *root = nullptr;
    generateFullBST(root, 8);
    printTree(root);
    return 0;
}
