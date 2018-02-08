/*
 * Exercise 4.32
 * Author: sesiria  2018
 * Algorithm to verify the binary search is legal for searching.
 * time complexity O(N)
 */

#include <algorithm>
#include <iostream>
#include <ostream>

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

#define MIN_NODE (0)
#define MAX_NODE (255)
/**
 * Algorithm to verify the binary search is legal for searching.
 * complexity O(N)
 */
template <typename Comparable>
bool verifyBinarySearchTree(BinaryNode<Comparable> *node)
{
    return verifyBinaryNode(node, MIN_NODE, MAX_NODE);
}

template <typename Comparable>
bool verifyBinaryNode(BinaryNode<Comparable> *node, const Comparable &min, const Comparable &max)
{
    if (node == nullptr)
        return true;

    if (min < node->element && node->element < max)
        return (verifyBinaryNode(node->left, min, node->element) &&
                verifyBinaryNode(node->right, node->element, max));

    else
        return false;
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
void printTree(BinaryNode<Comparable> *node)
{
    if (node == nullptr)
        return;
    printTree(node->left);
    std::cout << node->element << " ";
    printTree(node->right);
}

int main(int argc, char **argv)
{
    BinaryNode<int> *root = nullptr;
    int a[] = {5, 4, 3, 7, 9, 12, 6, 1, 14, 8};
    for (int i = 0; i < _countof(a); ++i)
        insert(a[i], root);

    printTree(root);
    std::cout << std::endl;
    std::cout << (verifyBinarySearchTree(root) ? "legal Tree" : "illegal tree") << std::endl;
    root->element = 2;
    std::cout << (verifyBinarySearchTree(root) ? "legal Tree" : "illegal tree") << std::endl;
    return 0;
}
