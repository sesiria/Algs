/*
 * Exercise 4.22
 * Author: sesiria  2018
 * BinarySearchTree implementation by lazy deletion.
 */

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

/**
 *  verify the AvlTree is balanded.
 *  and the height information is property maintainced.
 *  time complexiyt O(N)
 *  return value, normal is the height of the subtree. -1 for null.
 *  -2 for unbalanced occured/ height mistmatched.
 *  positive number is illegal.
 */ 
#define ILLEGAL_AVLTREENODE (-2)
template <typename Comparable>
int verifyAvlTree(AvlNode<Comparable> * node)
{
    if(node == nullptr)
        return -1;

    int left, right, height;
    if((left = verifyAvlTree(node->left) == ILLEGAL_AVLTREENODE))
        return ILLEGAL_AVLTREENODE; // unbalanced
    else if((right = verifyAvlTree(node->right) == ILLEGAL_AVLTREENODE))
        return ILLEGAL_AVLTREENODE; // unbalanced
    else if(left - right > 1 || right - left > 1) // unbalanced.
        return ILLEGAL_AVLTREENODE;
    else if((height = std::max(left, right) + 1) != node->height) // height mismatched.
        return ILLEGAL_AVLTREENODE;
    else
        return height;
}


int main(int argc, char **argv)
{


    return 0;
}
