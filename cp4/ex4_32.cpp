/*
 * Exercise 4.31
 * Author: sesiria  2018
 * Algorithm to verify the binary search is legal for searching.
 */

#include <algorithm>
#include <iostream>
#include <ostream>
#include <stack>

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
 * Algorithm to verify the binary search is legal for searching.
 * complexity O(N)
 */  
template <typename Comparable>
bool verifyBinarySearchTree(BinaryNode<Comparable> *node)
{

}


template <typename Comparable>
void printTree(BinaryNode<Comparable> *node)
{
    if (node == nullptr)
        return;
    bool bBrace = false;
    if (node->left || node->right)
        bBrace = true;
    if (bBrace)
        std::cout << "(";
    printTree(node->left);
    std::cout << node->element;
    printTree(node->right);

    if (bBrace)
        std::cout << ")";
}

int main(int argc, char **argv)
{

    return 0;
}
