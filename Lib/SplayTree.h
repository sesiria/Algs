/**
 * Author: sesiria  2018
 * SplayTree bottom-top access/rotation implementation.
 * Add parent node for rotations.
 */
#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <algorithm>
#include <iostream>
#include <ostream>

template <typename Comparable>
class SplayTree
{
  private:
    struct SplayNode
    {
        Comparable element;
        SplayNode *left;
        SplayNode *right;
        SplayNode *parent;

        SplayNode(const Comparable &theElement, SplayNode *lt, SplayNode *rt, SplayNode *pa)
            : element{theElement}, left{lt}, right{rt}, parent{pa}
        {
        }

        SplayNode(Comparable &&theElement, SplayNode *lt, SplayNode *rt, SplayNode *pa)
            : element{std::move(theElement)}, left{lt}, right{rt}, parent{pa}
        {
        }
    };

    /**
     * This routine will do single rotation the splay tree for left rotation.
     * time complexity O(1)
     */
    void singleLeftRotation(SplayNode *t)
    {
        // at first do the rotation for subnode.
        SplayNode *parent = t->parent;
        SplayNode *k1 = t->left;
        t->left = k1->right;
        if (k1->right)
            k1->right->parent = t;
        k1->right = t;
        t->parent = k1;
        // then we connect to the new subtree to the parent node.
        if (parent == nullptr) // t is the root we need to update the root.
            root = k1;
        else if (parent->left == t)
            parent->left = k1;
        else
            parent->right = k1;
        k1->parent = parent;
    }

    /**
     * This routine will do single rotation the splay tree for right rotation.
     */
    void singleRightRotation(SplayNode *t)
    {
        // at first do the rotation for subnode.
        SplayNode *parent = t->parent;
        SplayNode *k1 = t->right;
        t->right = k1->left;
        if (k1->left)
            k1->left->parent = t;
        k1->left = t;
        t->parent = k1;
        // then we connect to the new subtree to the parent node.
        if (parent == nullptr) // t is the root we need to update the root.
            root = k1;
        else if (parent->left == t)
            parent->left = k1;
        else
            parent->right = k1;
        k1->parent = parent;
    }

    /**
     * Splay Tree Node Rotation implementations.
     */
    void SplayTreeRotation(SplayNode *node)
    {
        while (node && node->parent)
        {
            if (node->parent == root) // single rotations.
            {
                if (node == node->parent->left)
                    singleLeftRotation(node->parent); // the node is the left child
                else
                    singleRightRotation(node->parent); // the node is the right child
            }
            else if (node->parent && node->parent->parent) // need double rotation.
            {
                SplayNode *grandParent = node->parent->parent;
                SplayNode *parent = node->parent;
                if (node == parent->left && parent == grandParent->left) // left zig-zig double rotation.
                {
                    singleLeftRotation(node->parent->parent);
                    singleLeftRotation(node->parent);
                }
                else if (node == parent->right && parent == grandParent->left) // left zig-zag double rotation.
                {
                    singleRightRotation(node->parent);
                    singleLeftRotation(node->parent);
                }
                else if (node == parent->right && parent == grandParent->right) // right zig-zig double rotation.
                {
                    singleRightRotation(node->parent->parent);
                    singleRightRotation(node->parent);
                }
                else // right zig-zag double rotation.
                {
                    singleLeftRotation(node->parent);
                    singleRightRotation(node->parent);
                }
            }
        }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, SplayNode *&t, SplayNode *parent)
    {
        if (t == nullptr)
        {
            t = new SplayNode{x, nullptr, nullptr, parent};
            ++theSize;
            SplayTreeRotation(t);
        }
        else if (x < t->element)
            insert(x, t->left, t);
        else if (t->element < x)
            insert(x, t->right, t);
        else
            ; // Duplicate; do nothiing
    }

    void makeEmpty(SplayNode *&t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            --theSize;
        }
        t = nullptr;
    }

    void clone(SplayNode *&t, SplayNode *pa, SplayNode *r)
    {
        if (r == nullptr)
            return;
        t = new SplayNode{r->element, nullptr, nullptr, pa};
        clone(t->left, t, r->left);
        clone(t->right, t, r->right);
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return code containing the smallest item.
     */
    SplayNode *findMin(SplayNode *t)
    {
        if (t != nullptr)
            while (t->left != nullptr)
                t = t->left;
        SplayTreeRotation(t);
        return t;
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largetst item.
     */
    SplayNode *findMax(SplayNode *t)
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        SplayTreeRotation(t);
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains(const Comparable &x, SplayNode *t)
    {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
        {
            SplayTreeRotation(t);
            return true;
        }
    }
    /**
     * Internal method to print a subtree rooted at t in sorted order.
     * Inorder traversal.
     */
    void printTree(SplayNode *t, std::ostream &out = std::cout) const
    {
        if (t != nullptr)
        {
            printTree(t->left, out);
            out << t->element << std::endl;
            printTree(t->right, out);
        }
    }

  public:
    SplayTree()
        : root{nullptr}, theSize{0}
    {
    }

    ~SplayTree()
    {
        makeEmpty(root);
    }

    // Copy Constructor
    SplayTree(const SplayTree & rhs)
        : root{nullptr}, theSize{rhs.theSize}
    {
        clone(root, nullptr, rhs.root);
    }

    // Copy assignment
    SplayTree & operator=(const SplayTree & rhs)
    {
        SplayTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    // Move Constructor
    SplayTree(SplayTree && rhs)
        :root{rhs.root}, theSize{rhs.theSize}
    {
        rhs.root = nullptr;
        rhs.theSize = 0;
    }

    // Move assignment
    SplayTree & operator=(SplayTree && rhs)
    {
        std::swap(root, rhs.root);
        std::swap(theSize, rhs.theSize);
        return *this;
    }

    void insert(const Comparable &x)
    {
        insert(x, root, nullptr);
    }

    void remove(const Comparable &x)
    {
        // can't find the key just return.
        if (!contains(x, root))
            return;

        SplayNode *right = root->right; // right subtree
        SplayNode *left = root->left;   // left subtree

        delete root;        // delete curernt node.
        if (left != nullptr && right != nullptr) // the left and the right are all nonempty.
        {
            root = left;
            left->parent = nullptr;
            findMax(root);
            root->right = right;  // relink to right subtree.
            right->parent = root;
        }
        else    // none or just one subtree is empty.
        {
            root = left ? left : right;
            if(root)
                root->parent = nullptr;
        }
    }

    void printTree()
    {
        printTree(root);
    }

  private:
    SplayNode *root;
    int theSize;
};

#endif