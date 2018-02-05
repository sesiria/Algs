/*
 * Exercise 4.12
 * Author: sesiria  2018
 * An implementation of map Class. Actually we need to use the red-black tree.
 * But the detail is discussed in Chapter 12.
 * We use the normal BinarySearchTree to instead.
 */
#include <algorithm>
#include <assert.h>
#include <iostream>

template <typename KeyType, typename ValueType>
struct Pair
{
    KeyType first;
    ValueType second;

    bool operator<(const Pair<KeyType, ValueType> &rhs) const
    {
        return first < rhs.first;
    }

    //Pair& operator

    bool operator<(const KeyType &key)
    {
        return first < key;
    }

    Pair(const KeyType &key, const ValueType &val)
        : first{key}, second{val}
    {
    }

    Pair(KeyType &&key, ValueType &&val)
        : first{std::move(key)}, second{std::move(val)}
    {
    }
};

template <typename KeyType, typename ValueType>
class Map
{
  private:
    struct BinaryNode
    {
        Pair<KeyType, ValueType> element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode *parent;

        BinaryNode(const Pair<KeyType, ValueType> &theElement,
            BinaryNode *lt = nullptr, BinaryNode *rt = nullptr, BinaryNode *pa = nullptr)
            : element{theElement}, left{lt}, right{rt}, parent{pa}
        {
        }

        BinaryNode(KeyType &&theElement, BinaryNode *lt = nullptr, 
            BinaryNode *rt = nullptr, BinaryNode *pa = nullptr)
            : element{std::move(theElement)}, left{lt}, right{rt}, parent{pa}
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

        const Pair<KeyType, ValueType> &operator*() const
        {
            return retrieve();
        }

        const Pair<KeyType, ValueType> *operator->() const
        {
            return &retrieve();
        }

        // prefix increament operator
        const_iterator &operator++()
        {
            if (current->right)
            {
                BinaryNode *t = current->right;
                while (t->left != nullptr)
                    t = t->left;
                current = t;
            }
            else
            {
                BinaryNode *t = current->parent;
                // found an parent to traversal next.
                // the element of parent must great then current.
                while (t && t->element < current->element)
                    t = t->parent;
                current = t;
            }
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
            if (current->left)
            {
                BinaryNode *t = current;
                while (t->left != nullptr)
                    t = t->left;
                current = t;
            }
            else
            {
                BinaryNode *t = current->parent;
                // found the parent to traversal previous.
                // the element of the parent must less then the current.
                while (t && current->element < t->element)
                    t = t->parent;
                current = t;
            }
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

        Pair<KeyType, ValueType> &retrieve() const
        {
            return current->element;
        }

        // protected implicity constructor for friend/derived class.
        const_iterator(BinaryNode *p)
            : current{p}
        {
        }

        friend class Map<KeyType, ValueType>;
    };

    // nested iterator class for Map class
    class iterator : public const_iterator
    {
      public:
        iterator() : const_iterator{nullptr}
        {
        }

        Pair<KeyType, ValueType> &operator*()
        {
            return const_iterator::retrieve();
        }

        const Pair<KeyType, ValueType> &operator*() const
        {
            return const_iterator::operator*();
        }

        Pair<KeyType, ValueType>* operator->()
        {
            return &const_iterator::retrieve();
        }

        const Pair<KeyType, ValueType>* operator->() const
        {
            return const_iterator::operator->();
        }

        // prefix increament operator.
        iterator &operator++()
        {
            if (this->current->right)
            {
                BinaryNode *t = this->current->right;
                while (t->left != nullptr)
                    t = t->left;
                this->current = t;
            }
            else
            {
                BinaryNode *t = this->current->parent;
                // found an parent to traversal next.
                // the element of parent must great then current.
                while (t && t->element < this->current->element)
                    t = t->parent;
                this->current = t;
            }
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
            if (this->current->left)
            {
                BinaryNode *t = this->current;
                while (t->left != nullptr)
                    t = t->left;
                this->current = t;
            }
            else
            {
                BinaryNode *t = this->current->parent;
                // found the parent to traversal previous.
                // the element of the parent must less then the current.
                while (t && this->current->element < t->element)
                    t = t->parent;
                this->current = t;
            }
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

        friend class Map<KeyType, ValueType>;
    };

  public:
    // the big-five member function
    // constructor.
    Map()
        : theSize{0},
          root{nullptr}
    {
    }

    // destructor.
    ~Map()
    {
        clear();
    }

    // copy constructor.
    Map(const Map &rhs)
        : theSize{rhs.theSize}
    {
        clone(root, nullptr, rhs.root);
    }

    // copy assignment
    Map &operator=(const Map &rhs)
    {
        Map copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    // move constructor.
    Map(Map &&rhs)
        : theSize{rhs.theSize},
          root{rhs.root}
    {
        rhs.theSize = 0;
        rhs.root = nullptr;
    }

    // move assignment
    Map &operator=(Map &&rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(root, rhs.root);
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
        return {findMin(root)};
    }

    const_iterator begin() const
    {
        return {findMin(root)};
    }

    iterator end()
    {
        return {nullptr};
    }

    const_iterator end() const
    {
        return {nullptr};
    }

    // public member.
    iterator insert(const Pair<KeyType, ValueType> &x)
    {
        return insert(x, root, nullptr);
    }

    iterator insert(iterator hint, const Pair<KeyType, ValueType> &x)
    {
        BinaryNode *node = hint.current;
        // check legal.
        if (node && node->parent)
        {
            if (node->element < node->parent->element && x < node->parent->element)
                return insert(x, node, node->parent);
            else if (node->parent->element < node->element && node->parent->element < x)
                return insert(x, node, node->parent);
        }
        else
            return insert(x);
    }

    int erase(const KeyType &x)
    {
        return remove(x, root) ? 1 : 0;
    }

    iterator erase(iterator itr)
    {
        BinaryNode *p = itr.current;
        if (p)
        { // we must update the link to the parent.
            if (p->parent)
                return {remove(p->element,
                               p->element < p->parent->element ? p->parent->left : p->parent->right)};
            else // the node have no parent , so it is the root.
                return {remove(p->element, root)};
        }
        return {nullptr};
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

    // private insert method.
    iterator insert(const Pair<KeyType, ValueType> &x,
                    BinaryNode *&t,
                    BinaryNode *parent)
    {
        if (t == nullptr)
        {
            theSize++; // increase the size.
            return {t = new BinaryNode{x, nullptr, nullptr, parent}};
        }
        else if (x < t->element)
            return insert(x, t->left, t);
        else if (t->element < x)
            return insert(x, t->right, t);

        return {t}; // already existed.
    }

    void clone(BinaryNode *&t, BinaryNode *pa, BinaryNode *r)
    {
        if (r == nullptr)
            return;
        t = new BinaryNode{r->element, nullptr, nullptr, pa};
        clone(t->left, t, r->left);
        clone(t->right, t, r->right);
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
     * Map the new root of the subtree.
     */
    BinaryNode *remove(const KeyType &x, BinaryNode *&t)
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
            iterator itr{t};
            ++itr;
            if (t->left)
                t->left->parent = t->parent; // update parent
            else if (t->right)
                t->right->parent = t->parent; // update parent
            t = (t->left != nullptr) ? t->left : t->right;

            delete oldNode;
            --theSize;
            return itr.current;
        }
    }
};

int main(int argc, char **argv)
{
    int a[] = {5, 4, 3, 7, 9, 12, 6, 14, 1, 8};
    Map<int, int> maps;
    for (int i = 0; i < _countof(a); ++i)
        maps.insert({a[i], i});

    for (auto iter = maps.begin(); iter != maps.end(); ++iter)
        std::cout << iter->first << " " << iter->second << std::endl;
    return 0;
}