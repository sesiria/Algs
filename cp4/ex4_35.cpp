/*
 * Exercise 4.35
 * Author: sesiria  2018
 * generate AVL Tree with height h and fewest node.
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
 * time complexity is O(a^N) a = 5/3
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
        t->right = generateAVLSubTree(height - 2, last);
    }
    return t;
}

/**
 * generateAVLTree with height h and fewest node.
 */
template <typename Comparable>
void generateAVLTree(AvlNode<Comparable> *&t, int height)
{
    init initialKey = 1;
    t = generateAVLSubTree(height, initialKey);
}



int main(int argc, char **argv)
{
    AvlNode<int> *root = nullptr;
    generateAVLTree(root, 32);
    makeEmpty(root);
    return 0;
}
