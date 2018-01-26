#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <algorithm>
#include <iostream>
#include <ostream>

template <typename Comparable>
class BinarySearchTree
{

  public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &rhs);
    BinarySearchTree(BinarySearchTree &&rhs);
    ~BinarySearchTree();

    const Comparable &findMin() const;
    const Comparable &findMax() const;
    // return true if x is found in the tree.
    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }
    bool isEmpty() const;
    void printTree(std::ostream &out = std::cout) const;

    void makeEmpty();

    // insert x into the tree; duplicates are ignored.
    void insert(const Comparable &x)
    {
        insert(x, root);
    }

    void insert(Comparable &&x);

    // remove x from the tree. Nothing is done if x is not found.
    void remove(const Comparable &x)
    {
        remove(x, root);
    }

    BinarySearchTree &operator=(const BinarySearchTree &rhs);
    BinarySearchTree &operator=(BinarySearchTree &&rhs);

  private:
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

    BinaryNode *root; // pointer to the root node of the BinarySearchTree

    // private member for recursive calling.
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, BinaryNode *&t)
    {
        if(t == nullptr)
            t = new BinaryNode{x, nullptr, nullptr};
        else if(x < t->element)
            insert(x, t->left);
        else if(t->element < x)
            insert(x, t->right);
        else
            ; // Duplicate; do nothiing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(Comparable &&x, BinaryNode *&t)
    {
        if(t == nullptr)
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        else if(x < t->element)
            insert(std::move(x), t->left);
        else if(t->element < x)
            insert(std::move(x), t->right);
        else
            ; // Duplicate; do nothiing
    }

    void remove(const Comparable &x, BinaryNode *&t);

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return code containing the smallest item.
     */ 
    BinaryNode *findMin(BinaryNode *t) const
    {
        if(t == nullptr)
            return nullptr;
        if(t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largetst item.
     */ 
    BinaryNode *findMax(BinaryNode *t) const
    {
        if(t != nullptr)
            while(t->right != nullptr)
                t = t->right;
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains(const Comparable &x, BinaryNode *t) const
    {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true;        // Match
    }
    void makeEmpty(BinaryNode *&t);
    void printTree(BinaryNode *t, std::ostream &out) const;
    BinaryNode *clone(BinaryNode *t) const;
};

#endif