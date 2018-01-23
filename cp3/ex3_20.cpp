/*
 * Exercise 3.20
 * Author: sesiria  2018
 * double linklist class. 
 * Lazy deletion routine for List class
 * update the code directly in list class.
 */
#include <iostream>
#include <algorithm>
#include <exception>

class IteratorMismatchException : public std::exception{
public:
    virtual const char*
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT
    {
        return "IteratorMismatchException";
    }
};

class IteratorOutofBoundsException : public std::exception{
public:
    virtual const char*
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT
    {
        return "IteratorOutofBoundsException";
    }
};

template<typename Object>
class List
{
    private:
        // Nested Node class for List class.
        struct Node
        {
            Object  data;       // store the element data.
            Node    *prev;      // point to the previous node.
            Node    *next;      // point to the next node.
            bool    isDeleted;  // mark that whether the element is deleted.

            Node(const Object &d = Object{}, Node *p = nullptr, Node *n = nullptr)
                : data{d},
                prev{p},
                next{n},
                isDeleted{false}
            {}

            Node(Object && d, Node * p = nullptr, Node * n = nullptr)
                : data{std::move(d)},
                prev(p),
                next{n},
                isDeleted{false}
            {}
        };
    
    public:
        // Nested const_iterator class for List class
        class const_iterator
        {
        public:
            const_iterator() : current{nullptr}
            {}

            const Object & operator* () const
            {
                return retrieve();
            }

            // prefix increament operator
            const_iterator & operator++ ()
            {
                current = current->next;
                return *this;
            }

            // postfix increament operator
            const_iterator operator++ (int)
            {
                const_iterator old = *this;
                ++(*this);
                return old;
            }

            // prefix decreament operator
            // update from exercise3.13
            const_iterator &operator--()
            {
                current = current->prev;
                return *this;
            }

            // postfix decreament operator
            // update from exercise3.13
            const_iterator operator--(int)
            {
                const_iterator old = *this;
                --(*this);
                return old;
            }

            // generate a new iterator with a steps ofk steps from the current iterator.
            // update from exercise3.14
            // without boundary check.
            const_iterator operator+(int k) const
            {
                const_iterator advance = *this;
                for (int i = 0; i < k; ++i)
                {
                    advance.current = advance.current->next;
                }
                return advance;
            }

            bool operator== (const const_iterator & rhs) const
            {
                return current == rhs.current;
            }

            bool operator!= (const const_iterator & rhs) const
            {
                return !(*this == rhs);
            }

          protected:
            const List *theList;
            Node * current;
            
            Object & retrieve() const
            {
                return current->data;
            }

            // protected implicity constructor for friend/derived class.
            const_iterator(const List & list, Node * p) 
            : theList{&list}, current{p}
            {}

            void assertIsValid() const
            {
                if(theList == nullptr || current == nullptr || current == theList->head)
                    throw IteratorOutofBoundsException{};
            }

            friend class List<Object>;
        };

        // nested iterator class for List class
        class iterator : public const_iterator
        {
        public:
            iterator()
            {}

            Object & operator* ()
            {
                return const_iterator::retrieve();
            }

            const Object & operator* () const
            {
                return const_iterator::operator*();
            }

            // prefix increament operator.
            iterator & operator++()
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
            // update from exercise 3.13
            iterator & operator--()
            {
                this->current = this->current->prev;
                return *this;
            }

            // postfix decreament operator.
            // update from exercise 3.13
            iterator operator--(int)
            {
                iterator old = *this;
                --(*this);
                return old;
            }

            // generate a new iterator with a steps ofk steps from the current iterator.
            // update from exercise3.14
            // without boundary check.
            iterator operator+(int k) const
            {
                iterator advance = *this;
                for (int i = 0; i < k; ++i)
                {
                    advance.current = advance.current->next;
                }
                return advance;
            }

          protected:
            iterator(const List & lst, Node * p) : const_iterator{lst, p}
            {}

            friend class List<Object>;
        };

        // Nested const_reverse_iterator class for List class
        // update from exercise 3_16
        class const_reverse_iterator
        {
        public:
            const_reverse_iterator() : current{nullptr}
            {}

            const Object & operator* () const
            {
                return retrieve();
            }

            // prefix increament operator
            const_reverse_iterator & operator++ ()
            {
                current = current->prev;
                return *this;
            }

            // postfix increament operator
            const_reverse_iterator operator++ (int)
            {
                const_reverse_iterator old = *this;
                ++(*this);
                return old;
            }

            bool operator== (const const_reverse_iterator & rhs) const
            {
                return current == rhs.current;
            }

            bool operator!= (const const_reverse_iterator & rhs) const
            {
                return !(*this == rhs);
            }

          protected:
            const List *theList;
            Node * current;
            
            Object & retrieve() const
            {
                return current->data;
            }

            // protected implicity constructor for friend/derived class.
            const_reverse_iterator(const List & lst, Node * p) 
            :theList{&lst},
             current{p}
            {}

            void assertIsValid() const
            {
                if(theList == nullptr || current == nullptr || current == theList->tail)
                    throw IteratorOutofBoundsException{};
            }

            friend class List<Object>;
        };


        // nested reverse_iterator class for List class
        // update from exercise 3_16
        class reverse_iterator : public const_reverse_iterator
        {
        public:
            reverse_iterator()
            {}

            Object & operator* ()
            {
                return const_reverse_iterator::retrieve();
            }

            const Object & operator* () const
            {
                return const_reverse_iterator::operator*();
            }

            // prefix increament operator.
            reverse_iterator & operator++()
            {
                this->current = this->current->prev;
                return *this;
            }

            // postfix increament operator.
            reverse_iterator operator++(int)
            {
                reverse_iterator old = *this;
                ++(*this);
                return old;
            }

          protected:
            reverse_iterator(const List &lst, Node * p) : const_reverse_iterator{lst, p}
            {}

            friend class List<Object>;
        };


    public:
        // default constructor.
        List()
        {
            init();
        }

        // copy constructor.
        List(const List & rhs)
        {
            init();
            for( auto & x : rhs)
                push_back(x);
        }

        // default destructor.
        ~List()
        {   
            clear();
            delete head;
            delete tail;
        }

        // copy assignment.
        List & operator= (const List &rhs)
        {
            List copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        // move constructor.
        List(List && rhs)
            : theSize{rhs.theSize},
            countDeleted{rhs.countDeleted},
            head{rhs.head},
            tail{rhs.tail}
        {
            rhs.theSize = 0;
            rhs.countDeleted = 0;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }

        // move assignment.
        List & operator= (List && rhs)
        {
            std::swap(theSize, rhs.theSize);
            std::swap(countDeleted, rhs.countDeleted);
            std::swap(head, rhs.head);
            std::swap(tail, rhs.tail);
            
            return *this;
        }

        iterator begin()
        {
            return {*this, head->next};
        }

        const_iterator begin() const
        {
            return {*this, head->next};
        }

        reverse_iterator rbegin()
        {
            return {*this, tail->prev};
        }

        const_reverse_iterator rbegin() const
        {
            return {*this, tail->prev};
        }

        iterator end()
        {
            return {*this, tail};
        }

        const_iterator end() const
        {
            return {*this, tail};
        }

        reverse_iterator rend()
        {
            return {*this, head};
        }

        const_reverse_iterator rend() const
        {
            return {*this, head};
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
            while(!empty())
                pop_front();
        }

        Object &front()
        {
            return *begin();
        }

        const Object & front() const
        {
            return *begin();
        }

        Object & back()
        {
            return *--end();
        }

        const Object & back() const
        {
            return *--end();
        }

        void push_front(const Object & x)
        {
            insert(begin(), x);
        }

        void push_front(Object && x)
        {
            insert(begin(), std::move(x));
        }

        void push_back(const Object & x)
        {
            insert(end(), x);
        }

        void push_back(Object && x)
        {
            insert(end(), std::move(x));
        }

        void pop_front()
        {
            erase(begin());
        }

        void pop_back()
        {
            erase(--end());
        }

        // insert x before itr.
        // return the iterator which includes the position of the new generated element.
        iterator insert(iterator itr, const Object &x)
        {
            itr.assertIsValid();
            if(itr.theList != this)
                throw IteratorMismatchException{};
            Node *p = itr.current;
            theSize++;
            return {p->prev = p->prev->next = new Node{x, p->prev, p}};
        }

        // insert x before itr
        // return the iterator which includes the position of the new generated element.
        iterator insert(iterator itr, Object && x)
        {
            itr.assertIsValid();
            if(itr.theList != this)
                throw IteratorMismatchException{};
            Node *p = itr.current;
            theSize++;
            return {*this, p->prev = p->prev->next = new Node{std::move(x), p->prev, p}};            
        }

        // Erase item at itr.
        // return the iterator of the next position before delete the element.
        iterator erase(iterator itr)
        {
            itr.assertIsValid();
            if(itr.theList != this)
                throw IteratorMismatchException{};
            Node *p = itr.current;
            iterator retVal{*this, p->next};
            p->prev->next = p->next;
            p->next->prev = p->prev;
            // if the element has been mark by deleted.
            if(p->isDeleted == true)
                countDeleted--;
            delete p;
            theSize--;

            return retVal;
        }

        iterator erase(iterator from, iterator to)
        {
            from.assertIsValid();
            to.assertIsValid();
            if(from.theList != this)
                throw IteratorMismatchException{};
            if(to.theList != this)
                throw IteratorMismatchException{};

            for (iterator itr = from; itr != to;)
                itr = erase(itr);
        }

        // update from exercise 3.15
        // splice list
        // limitation time O(1)
        void splice(iterator position, List & list)
        {
            // can't splice the same list.
            position.assertIsValid();
            if(position.theList != this)
                throw IteratorMismatchException();

            if(this == &list)
                return;

            Node *p = position.current;
            p->prev->next = list.head->next;
            list.head->next->prev = p->prev;
            p->prev = list.tail->prev;
            list.tail->prev->next = p;
            theSize += list.theSize; // increase the size.

            // reset the list
            list.head->next = list.tail;
            list.tail->prev = list.head;
            list.theSize = 0;
        }

        // lazy delete rountine.
        void deleteElement(iterator position)
        {
            position.assertIsValid();
            if(position.theList != this)
                throw IteratorMismatchException{};

            (*position)->isDeleted = true; // mark as deleted.
            ++countDeleted;

            lazyDeletion();
        }

      private:
        int     theSize;  // the size of the linklist (number of elements)
        int     countDeleted;   // count the number of elements be deleted.
        Node    *head;
        Node    *tail;
        

        // init method.
        void init()
        {
            theSize = 0;
            countDeleted = 0;
            head = new Node;
            tail = new Node;
            head->next = tail;
            tail->prev = head;
        }

        // process lazy deletetion.
        void lazyDeletion()
        {
            if(countDeleted > theSize / 2)
            {
                for (auto iter = begin(); iter != end();)
                {
                    if((*iter)->isDeleted == true)
                        iter = erase(iter);
                    else
                        ++iter;
                }
            }
        }
};


int main(int argc, char **argv)
{
    

    return 0;
}