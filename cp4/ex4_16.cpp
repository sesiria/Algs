/*
 * Exercise 4.16
 * Author: sesiria  2018
 * BinarySearchTree implementation by lazy deletion.
 */

#include <algorithm>
#include <iostream>
#include <ostream>

template <typename Comparable>
class BinarySearchTree
{

  public:
    BinarySearchTree()
        : root{nullptr}, theSize{0}, theSizeDeleted{0}
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree &rhs)
        : theSize{rhs.theSize}, theSizeDeleted{rhs.theSizeDeleted}
    {
        root = clone(rhs.root);
    }

    /**
     * Move constructor
     */
    BinarySearchTree(BinarySearchTree &&rhs)
        : root{rhs.root}, theSize{rhs.theSize}, theSizeDeleted{rhs.theSizeDeleted}
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
        return (theSize == 0);
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(std::ostream &out = std::cout) const
    {
        if (isEmpty())
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
        std::swap(theSize, rhs.theSize);
        std::swap(theSizeDeleted, rhs.theSizeDeleted);
        return *this;
    }

  private:
    struct BinaryNode
    {
        bool bDeleted;
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : bDeleted{false}, element{theElement}, left{lt}, right{rt}
        {
        }

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
            : bDeleted{false}, element{std::move(theElement)}, left{lt}, right{rt}
        {
        }
    };

    BinaryNode *root; // pointer to the root node of the BinarySearchTree
    int theSize;
    int theSizeDeleted;

    // private member for recursive calling.
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, BinaryNode *&t)
    {
        if (t == nullptr)
        {
            t = new BinaryNode{x, nullptr, nullptr};
            ++theSize;
        }
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else if (t->bDeleted) // if the node has been mark by deleted, just restored the node.
        {
            t->bDeleted = false;
            --theSizeDeleted;
        }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(Comparable &&x, BinaryNode *&t)
    {
        if (t == nullptr)
        {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
            ++theSize;
        }
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (t->element < x)
            insert(std::move(x), t->right);
        else if (t->bDeleted) // if the node has been mark by deleted, just restored the node.
        {
            t->bDeleted = false;
            --theSizeDeleted;
        }
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable &x, BinaryNode *&t)
    {
        if (t == nullptr)
            return; // item not found; do nothing
        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (!t->bDeleted) // if the node has not been mark by deleted , just mark.
        {
            t->bDeleted = true;
            ++theSizeDeleted;
        }
        else // otherwise do nothing.
        {
        }
        lazyDeletion();
    }

    // check lazy deletion.
    void lazyDeletion()
    {
        // half of the nodes have been marked by deleted. we just do a lazy deletion.
        if (theSizeDeleted == theSize / 2)
        {
            doRemove(root);
        }
    }

    // actual do the remove operaton from the binary search tree.
    void doRemove(BinaryNode *&t)
    {
        if (t == nullptr)
            return;
        // remove the children at first.
        doRemove(t->left);
        doRemove(t->right);

        if (t->bDeleted) // the current node should been deleted.
        {
            // until now, all the children markded by deleted has been removed.
            // two children and none of them have been marked by deleted.
            if (t->left != nullptr && t->right != nullptr)
            {
                BinaryNode *node = findMin(t->right);
                std::swap(t->element, node->element);
                std::swap(t->bDeleted, node->bDeleted);
                // we do an remove again to delete the children.
                doRemove(t->right);
            }
            else // one or none children.
            {
                BinaryNode *oldNode = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete oldNode;
                --theSizeDeleted;
                --theSize;
            }
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return code containing the smallest item.
     * ignore the node which has been mark by deleted.
     */
    BinaryNode *findMin(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t->bDeleted ? nullptr : t;
        BinaryNode *node = nullptr;
        return (node = findMin(t->left)) ? (node) : ((t->bDeleted) ? nullptr : t);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largetst item.
     * ignore the node which has been mark by deleted.
     */
    BinaryNode *findMax(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->right == nullptr)
            return t->bDeleted ? nullptr : t;
        BinaryNode *node = nullptr;
        return (node = findMin(t->right)) ? (node) : ((t->bDeleted) ? nullptr : t);
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
            return !t->bDeleted; // Match
    }
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(BinaryNode *&t)
    {
        if (t != nullptr)
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
        if (t != nullptr)
        {
            printTree(t->left, out);
            if(!t->bDeleted)
                out << t->element << std::endl;
            printTree(t->right, out);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode *clone(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

};

int main(int argc, char ** argv)
{
    int a[] = {2, 1, 4, 3, 8, 6, 7, 0, -1, -2}; //{5, 4, 3, 7, 9, 12, 6, 1, 14, 8};
    BinarySearchTree<int> tree;
    for (int i = 0; i < _countof(a); ++i)
        tree.insert(a[i]);

    tree.printTree();
    tree.remove(0);
    tree.remove(-1);
    tree.remove(-2);
    tree.remove(6);
    tree.insert(-1);
    tree.remove(4);
    tree.printTree();

    return 0;
}
