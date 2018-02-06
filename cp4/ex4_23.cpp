/*
 * Exercise 4.23
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
 * Return the height of node t or -1 if nullptr.
 */
template <typename Comparable>
int height(AvlNode<Comparable> *t)
{
    return t == nullptr ? -1 : t->height;
}

/**
 * This routine will rotation the avl tree for the case of 2
 * verifyAvlTree Will maintains the height of the node.
 */
template <typename Comparable>
void rotationForAVLTreeCase2(AvlNode<Comparable> *&t)
{
    AvlNode<Comparable> *k3 = t;
    AvlNode<Comparable> *k1 = k3->left;
    AvlNode<Comparable> *k2 = k1->right;
    k1->right = k2->left;
    k3->left = k2->right;
    k2->left = k1;
    k2->right = k3;
    k1->height = std::max(height(k1->left), height(k1->right)) + 1;
    k3->height = std::max(height(k3->left), height(k3->right)) + 1;
    k2->height = std::max(height(k2->left), height(k2->right)) + 1;
    t = k2;
}

int main(int argc, char **argv)
{

    return 0;
}
