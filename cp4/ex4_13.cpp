/*
 * Exercise 4.13
 * Author: sesiria  2018
 * An implementation of set Class. Actually we need to use the red-black tree.
 * But the detail is discussed in Chapter 12.
 * We use the normal BinarySearchTree to instead. With link to the next and previous node
 * And the head and tail node.
 */
#include <algorithm>
#include <assert.h>
#include <iostream>

template <typename Comparable>
class Set
{
  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode *prev;
        BinaryNode *next;

        BinaryNode(const Comparable &theElement, BinaryNode *lt = nullptr, 
            BinaryNode *rt = nullptr, BinaryNode *p = nullptr, BinaryNode *n = nullptr)
            : element{theElement}, left{lt}, right{rt}, prev{p}, next{n}
        {
        }

        BinaryNode(Comparable &&theElement, BinaryNode *lt = nullptr, 
            BinaryNode *rt = nullptr, BinaryNode *p = nullptr, BinaryNode *n = nullptr)
            : element{std::move(theElement)}, left{lt}, right{rt}, prev{p}, next{n}
        {
        }
    };

  public:
    // nested const_iterator class for List class
    class const_iterator
    {
      public:
        const_iterator() : current{nullptr}
        {
        }

        const Comparable &operator*() const
        {
            return retrieve();
        }

        // prefix increament operator
        const_iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        // postfix increament operator
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        // prefix decreament operator
        const_iterator &operator--()
        {
            current = current->prev;
            return *this;
        }

        // postfix decreament operator
        const_iterator operator--(int)
        {
            const_iterator old = *this;
            --(*this);
            return old;
        }

        bool operator==(const const_iterator &rhs) const
        {
            return current == rhs.current;
        }

        bool operator!=(const const_iterator &rhs) const
        {
            return !(*this == rhs);
        }

      protected:
        BinaryNode *current;

        Comparable &retrieve() const
        {
            return current->element;
        }

        // protected implicity constructor for friend/derived class.
        const_iterator(BinaryNode *p)
            : current{p}
        {
        }

        friend class Set<Comparable>;
    };

    // nested iterator class for Set class
    class iterator : public const_iterator
    {
      public:
        iterator() : const_iterator{nullptr}
        {
        }

        Comparable &operator*()
        {
            return const_iterator::retrieve();
        }

        const Comparable &operator*() const
        {
            return const_iterator::operator*();
        }

        // prefix increament operator.
        iterator &operator++()
        {
            this->current = this->current->next;
            return *this;
        }

        // postfix increament operator.
        iterator operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

        // prefix decreament operator.
        iterator &operator--()
        {
            this->current = this->current->prev;
            return *this;
        }

        // postfix decreament operator.
        iterator operator--(int)
        {
            iterator old = *this;
            --(*this);
            return old;
        }

      protected:
        iterator(BinaryNode *p) : const_iterator{p}
        {
        }

        friend class Set<Comparable>;
    };

  public:
    // the big-five member function
    // constructor.
    Set()
    {
        init();
    }

    // destructor.
    ~Set()
    {
        clear();
        delete head;
        delete tail;
    }

    // copy constructor.
    Set(const Set &rhs)
    {
        init();
        for (auto &x : rhs)
            insert(x);
    }

    // copy assignment
    Set &operator=(const Set &rhs)
    {
        Set copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    // move constructor.
    Set(Set &&rhs)
        : theSize{rhs.theSize},
          root{rhs.root},
          head{rhs.head},
          tail{rhs.tail}
    {
        rhs.theSize = 0;
        rhs.root = nullptr;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    // move assignment
    Set &operator=(Set &&rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(root, rhs.root);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
    }

    int size() const
    {
        return theSize;
    }

    bool empty() const
    {
        return size() == 0;
    }

    void clear()
    {
        makeEmpty(root);
    }

    iterator begin()
    {
        return {head->next};
    }

    const_iterator begin() const
    {
        return {head->next};
    }

    iterator end()
    {
        return {tail};
    }

    const_iterator end() const
    {
        return {tail};
    }

    // public member.
    iterator insert(const Comparable &x)
    {
        return insert(x, root, head, tail);
    }

    iterator insert(iterator hint, const Comparable &x)
    {
        BinaryNode *node = hint.current;
        // check legal.
        if (node && node->next && node->prev)
        {
            // prev < x < node
            if (x < node->element && node->prev->element < x)
                return insert(x, node->left, node->prev, node);

            // node < x < next
            else if (node->element < x && x < node->next->element)
                return insert(x, node->right, node, node->next);
        }
        // normal insert
        return insert(x);
    }

    int erase(const Comparable &x)
    {
        return remove(x, root) ? 1 : 0;
    }

    iterator erase(iterator itr)
    {
        BinaryNode *p = itr.current;
        if (p)
        { // we must update the link to the parent.
            return {remove(p->element, p)};
        }
        return itr; // didn't remove anything.
    }

    iterator erase(iterator start, iterator end)
    {
        iterator itr;
        for (itr = start; itr != end;)
            itr = erase(itr);
        return itr;
    }

  private:
    int theSize;
    BinaryNode *root; // pointer to the root node of the BinarySearchTree
    BinaryNode *head;
    BinaryNode *tail;

    // init method.
    void init()
    {
        theSize = 0;
        root = nullptr;
        head = new BinaryNode{Comparable{}};
        tail = new BinaryNode{Comparable{}};
        head->next = tail;
        tail->prev = head;
    }

    // private insert method.
    iterator insert(const Comparable &x,
                    BinaryNode *&t, BinaryNode *prev, BinaryNode *next)
    {
        if (t == nullptr)
        {
            theSize++; // increase the size.
            return {next->prev = prev->next = t = new BinaryNode{x, nullptr, nullptr, prev, next}};
        }
        else if (x < t->element)
            return insert(x, t->left, prev, t);
        else if (t->element < x)
            return insert(x, t->right, t, next);

        return {t}; // already existed.
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
            --theSize;
        }
        t = nullptr;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return code containing the smallest item.
     */
    BinaryNode *findMin(BinaryNode *t) const
    {
        if (t != nullptr)
            while (t->left != nullptr)
                t = t->left;
        return t;
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largetst item.
     */
    BinaryNode *findMax(BinaryNode *t) const
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
    BinaryNode *remove(const Comparable &x, BinaryNode *&t)
    {
        if (t == nullptr)
            return nullptr; // item not found; do nothing
        if (x < t->element)
            return remove(x, t->left);
        else if (t->element < x)
            return remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
            return t;
        }
        else // one children or none children
        {
            BinaryNode *oldNode = t;
            iterator itr{t->next};
            // relink double-linklist
            t->prev->next = t->next;
            t->next->prev = t->prev;
            // relink binarytree
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
            --theSize;
            return itr.current;
        }
    }
};

int main(int argc, char **argv)
{
    int a[] = {5, 4, 3, 7, 9, 12, 6, 1, 14, 8};
    Set<int> trees;
    for (int i = 0; i < _countof(a); ++i)
        trees.insert(a[i]);

    // test const_iterator
    for (Set<int>::const_iterator iter = trees.begin(); iter != trees.end(); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;

    trees.insert(--trees.end(), 15);

    Set<int> tree1 = trees;

    tree1.erase(5);
    tree1.erase(1);
    tree1.erase(14);
    tree1.erase(8);
    tree1.erase(0);
    tree1.erase(1);
    for (auto &x : tree1)
        std::cout << x << " ";
    std::cout << std::endl;

    tree1.erase(tree1.begin(), tree1.end());
    std::cout << "size of tree is " << tree1.size() << std::endl;
    return 0;
}