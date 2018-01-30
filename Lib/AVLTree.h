#ifndef AvlTree_H
#define AvlTree_H

#include <algorithm>
#include <iostream>
#include <ostream>

template <typename Comparable>
class AvlTree
{

  public:
    AvlTree() = default;

    /**
     * Copy constructor
     */
    AvlTree(const AvlTree &rhs)
    {
        root = clone(rhs.root);
    }

    /**
     * Move constructor
     */
    AvlTree(AvlTree &&rhs)
        : root{rhs.root}
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~AvlTree()
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

    void printTree(std::ostream &out = std::cout) const
    {
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

    void insert(Comparable &&x);

    // remove x from the tree. Nothing is done if x is not found.
    void remove(const Comparable &x)
    {
        remove(x, root);
    }

    AvlTree &operator=(const AvlTree &rhs)
    {
        AvlTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    AvlTree &operator=(AvlTree &&rhs)
    {
        std::swap(root, rhs.root);
    }

  private:
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

    AvlNode *root; // pointer to the root node of the AvlTree
    static const int ALLOWED_IMBALANCE = 1;

    // private member for recursive calling.
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, AvlNode *&t)
    {
        if (t == nullptr)
            t = new AvlNode{x, nullptr, nullptr};
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
            ; // Duplicate; do nothiing

        balance(t);
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(Comparable &&x, AvlNode *&t)
    {
        if (t == nullptr)
            t = new AvlNode{std::move(x), nullptr, nullptr};
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (t->element < x)
            insert(std::move(x), t->right);
        else
            ; // Duplicate; do nothiing
        balance(t);
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable &x, AvlNode *&t)
    {
        if (t == nullptr)
            return; // item not found; do nothing
        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else // one children or none children
        {
            AvlNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }

        balance(t);
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return code containing the smallest item.
     */
    AvlNode *findMin(AvlNode *t) const
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
    AvlNode *findMax(AvlNode *t) const
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains(const Comparable &x, AvlNode *t) const
    {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true; // Match
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void printTree(AvlNode *t, std::ostream &out) const
    {
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
    }

    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    /**
     * Assume t is balanced or within one of being balanced
     */
    void balance(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
        {
            if (height(t->left->left) >= height(t->left->right))    // the equal is occur when delete nodes.
            {
                rotateWithLeftChild(t);
            }
            else
            {
                doubleWithLeftChild(t);
            }
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
        {
            if (height(t->right->right) >= height(t->right->left))  // the equal is occur when delete nodes.
            {
                rotateWithRightChild(t);
            }
            else
            {
                doubleWithRightChild(t);
            }
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode * & k2) 
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case4.
     * Update heights, then set new root.
     */ 
    void rotateWithRightChild(AvlNode * & k2)
    {
        AvlNode *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2 = k1;
    }

    /**
     * Double rotate binary tree node: first left child
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode * & k3) 
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first left child
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode * & k3) 
    {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }
};

#endif