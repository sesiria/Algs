#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <algorithm>
#include <iostream>
#include <ostream>

template <typename Comparable>
class BinarySearchTree
{

  public:
    BinarySearchTree() = default;

    /**
     * Copy constructor
     */ 
    BinarySearchTree(const BinarySearchTree &rhs)
    {
        root = clone(rhs.root);
    }

    /**
     * Move constructor
     */ 
    BinarySearchTree(BinarySearchTree &&rhs)
        :root{rhs.root}
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */ 
    ~BinarySearchTree()
    {
        makeEmpty();
    }

    const Comparable &findMin() const
    {
        return findMin(root);
    }

    const Comparable &findMax() const
    {
        return findMax(root);
    }

    // return true if x is found in the tree.
    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }
    bool isEmpty() const
    {
        return (root == nullptr);
    }

    /**
     * Print the tree contents in sorted order.
     */ 
    void printTree(std::ostream &out = std::cout) const
    {
        if(isEmpty())
            out << "Empty tree" << std::endl;
        else
            printTree(root, out);
    }

    void makeEmpty()
    {
        makeEmpty(root);
    }

    // insert x into the tree; duplicates are ignored.
    void insert(const Comparable &x)
    {
        insert(x, root);
    }

    void insert(Comparable &&x)
    {
        insert(std::move(x), root);
    }

    // remove x from the tree. Nothing is done if x is not found.
    void remove(const Comparable &x)
    {
        remove(x, root);
    }

    BinarySearchTree &operator=(const BinarySearchTree &rhs)
    {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    BinarySearchTree &operator=(BinarySearchTree &&rhs)
    {
        std::swap(root, rhs.root);
        return *this;
    }

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

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */ 
    void remove(const Comparable &x, BinaryNode *&t)
    {
        if(t == nullptr)
            return; // item not found; do nothing
        if(x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if(t->left != nullptr && t->right != nullptr)  // two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else    // one children or none children
        {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }

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
    /**
     * Internal method to make subtree empty.
     */ 
    void makeEmpty(BinaryNode *&t)
    {
        if(t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */ 
    void printTree(BinaryNode *t, std::ostream &out) const
    {
        if(t != nullptr)
        {
            printTree(t->left, out);
            out << t->element << std::endl;
            printTree(t->right, out);
        }
    }

    /**
     * Internal method to clone subtree.
     */ 
    BinaryNode *clone(BinaryNode *t) const
    {
        if(t == nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

    /**
     * Internal method to compute the height of a subtree rooted at t.
     * Note thte the defintion of the leaf node with height 0.
     */ 
    int height(BinaryNode * t)
    {
        if(t == nullptr)
            return -1;
        else
            return 1 + max(height(t->left), height(t->right));
    }
};

#endif