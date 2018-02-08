/*
 * Exercise 4.33
 * Author: sesiria  2018
 * remove the leaves from an binary tree.
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

/**
 * remove all leaves from the binary tree.
 * time complexity O(N)
 */  
template <typename Comparable>
void removeLeaves(BinaryNode<Comparable> *&t)
{
    if(t == nullptr)
        return;
    else if(t->left == nullptr && t->right == nullptr) // leaf node
    {
        delete t;
        t = nullptr;
        return;
    }

    removeLeaves(t->left);
    removeLeaves(t->right);
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

    printTree(root);
    std::cout << std::endl;
    removeLeaves(root);
    printTree(root);
    std::cout << std::endl;
    return 0;
}
