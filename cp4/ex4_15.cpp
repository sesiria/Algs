/*
 * Exercise 4.15
 * Author: sesiria  2018
 * Remove node with two children.
 * a) Replace with the largest node, X ,in Tl and recursively remove X.
 * b) Alternately replace with the largest node in Tl and the smallest node in Tr, and recursively remove the appripariate node.
 * c) Replace with either the largest node in Tl or the smallest node in 
 * Tr(recursively removeing the ppropriate node), making the choice randomly.
 */
#include "../Lib/randomize.h"
#include <iostream>

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
 * Internal method to find the smallest item in a subtree t.
 * Return code containing the smallest item.
 */
template <typename Comparable>
BinaryNode<Comparable> *findMin(BinaryNode<Comparable> *t)
{
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findMin(t->left);
}

/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largetst item.
 */
template <typename Comparable>
BinaryNode<Comparable> *findMax(BinaryNode<Comparable> *t)
{
    if (t != nullptr)
        while (t->right != nullptr)
            t = t->right;
    return t;
}

/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template <typename Comparable>
void remove1(const Comparable &x, BinaryNode<Comparable> *&t)
{
    if (t == nullptr)
        return; // item not found; do nothing
    if (x < t->element)
        remove(x, t->left);
    else if (t->element < x)
        remove(x, t->right);
    else if (t->left != nullptr && t->right != nullptr) // two children
    {
        t->element = findMax(t->left)->element;
        remove(t->element, t->left);
    }
    else // one children or none children
    {
        BinaryNode<Comparable> *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
}

/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template <typename Comparable>
void remove2(const Comparable &x, BinaryNode<Comparable> *&t)
{
    static int removeCount = 0;
    if (t == nullptr)
        return; // item not found; do nothing
    if (x < t->element)
        remove(x, t->left);
    else if (t->element < x)
        remove(x, t->right);
    else if (t->left != nullptr && t->right != nullptr) // two children
    {
        if ((removeCount++) % 2)
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            t->element = findMax(t->left)->element;
            remove(t->element, t->left);
        }
    }
    else // one children or none children
    {
        BinaryNode<Comparable> *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
}

/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template <typename Comparable>
void remove3(const Comparable &x, BinaryNode<Comparable> *&t)
{
    if (t == nullptr)
        return; // item not found; do nothing
    if (x < t->element)
        remove(x, t->left);
    else if (t->element < x)
        remove(x, t->right);
    else if (t->left != nullptr && t->right != nullptr) // two children
    {
        if (randInt(0, 1) == 0)
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            t->element = findMax(t->left)->element;
            remove(t->element, t->left);
        }
    }
    else // one children or none children
    {
        BinaryNode<Comparable> *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
}

int main(int argc, char **argv)
{
    return 0;
}