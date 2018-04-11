#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#include <algorithm>

template <typename Comparable>
class LeftistHeap
{
  public:
    LeftistHeap()
        : root{nullptr}
    {
    }

    LeftistHeap(const LeftistHeap &rhs)
        : root{nullptr}
    {
        root = clone(rhs.root);
    }

    LeftistHeap(LeftistHeap &&rhs)
        : root{rhs.root}
    {
        rhs.root = nullptr;
    }

    ~LeftistHeap()
    {
        makeEmpty();
    }

    LeftistHeap &operator=(const LeftistHeap &rhs)
    {
        LeftistHeap copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    LeftistHeap &operator=(LeftistHeap &&rhs)
    {
        std::swap(this->root, rhs.root);
        return *this;
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

    Comparable &findMin()
    {
        if (isEmpty())
            std::__throw_underflow_error(
                "Try to delete element from an empty heap");

        return root->element;
    }

    const Comparable &findMin() const
    {
        if (isEmpty())
            std::__throw_underflow_error(
                "Try to delete element from an empty heap");

        return *root;
    }

    void insert(const Comparable &x)
    {
        root = merge(new LeftistNode{x}, root);
    }

    void insert(Comparable &&x)
    {
        root = merge(new LeftistNode{std::move(x)}, root);
    }

    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */
    void deleteMin()
    {
        if (isEmpty())
            std::__throw_underflow_error(
                "Try to delete element from an empty heap");

        LeftistNode *oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
    void deleteMin(Comparable &minItem)
    {
        minItem = findMin();
        deleteMin();
    }

    /**
     * Make the priority queue logically empty.
     */
    void makeEmpty()
    {
        reclaimMemory(root);
        root = nullptr;
    }

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     */
    void merge(LeftistHeap &rhs)
    {
        if (this == &rhs) // avoid aliasing problems
            return;

        root = merge(root, rhs.root);
        rhs.root = nullptr;
    }

  private:
    struct LeftistNode
    {
        Comparable element;
        LeftistNode *left;
        LeftistNode *right;
        int npl; // null path length

        LeftistNode(const Comparable &e, LeftistNode *lt = nullptr,
                    LeftistNode *rt = nullptr, int np = 0)
            : element{e}, left{lt}, right{rt}, npl{np}
        {
        }

        LeftistNode(Comparable &&e, LeftistNode *lt = nullptr,
                    LeftistNode *rt = nullptr, int np = 0)
            : element{std::move(e)}, left{lt}, right{rt}, npl{np}
        {
        }
    };

    LeftistNode *root;

    /**
     * Internal method to merge two roots.
     */
    LeftistNode *merge(LeftistNode *h1, LeftistNode *h2)
    {
        if (h1 == nullptr)
            return h2;
        if (h2 == nullptr)
            return h1;
        if (h1->element < h2->element)
            return merge1(h1, h2);
        else
            return merge1(h2, h1);
    }

    /**
     * Internal method to merge two roots.
     * Assumes trees are not empty, and h1's root contains smallest item.
     */
    LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2)
    {
        if (h1->left == nullptr) // single node
            h1->left = h2;       // other fields in h1 alread accurate
        else
        {
            h1->right = merge(h1->right, h2);
            if (h1->left->npl < h1->right->npl)
                swapChildren(h1);
            h1->npl = h1->right->npl + 1;
        }
        return h1;
    }

    /**
     * swaps i's children.
     */
    void swapChildren(LeftistNode *t)
    {
        std::swap(t->left, t->right);
    }

    /**
     * Internal method to make the tree empty.
     * WARNING: This is prone to running out of stack space;
     *          execises suggest a solution.
     */
    void reclaimMemory(LeftistNode *t)
    {
        if (t != nullptr)
        {
            reclaimMemory(t->left);
            reclaimMemory(t->right);
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to clone subtree.
     * WARNING: This is prone to running out of stack space.
     *          exercises suggest a solution.
     */
    LeftistNode *clone(LeftistNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new LeftistNode{t->element, clone(t->left), clone(t->right), t->npl};
    }
};

#endif