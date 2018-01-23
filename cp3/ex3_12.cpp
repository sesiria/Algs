/*
 * Exercise 3.12
 * Author: sesiria  2018
 * singly link list implementations.
 * basic method size, print, test, add, remove
 * It is a prototype of basic set.
 * base code inherit from exercise 3.11 
 * maintaining the singly linklist in sorted order.
 * not support for iteration.
 */
#include <algorithm>
#include <iostream>

// The Object must support the == , <, >, etc.operator
template <typename Comparable>
class LinkList
{
  private:
    struct Node
    {
        Comparable data; // store the data.
        Node *next;      // point to next node.
        Node(const Comparable &d = Comparable{}, Node *n = nullptr)
            : data{d},
              next{n}
        {
        }
    };

  public:
    // normal constructor.
    LinkList()
    {
        init();
    }

    // copy constructor.
    LinkList(const LinkList &rhs)
        : theSize{rhs.theSize}
    {
        init();
        Node *p = rhs.head->next; // get the first element from rhs.
        Node *h = head;
        while (p != nullptr)
        {
            Node *node = new Node{p->data};
            h->next = node;
            h = node;
            p = p->next; // traversel to next element from rhs.
        }
    }

    // destructor.
    ~LinkList()
    {
        Node *p = head;
        while (p != nullptr)
        {
            Node *cur = p;
            p = p->next; // traversel to next.
            delete cur;
        }
    }

    // copy assignment
    LinkList &operator=(const LinkList &rhs)
    {
        LinkList list = rhs;
        std::swap(*this, list);
        return *this;
    }

    // move constructor.
    LinkList(LinkList &&rhs)
        : head{rhs.head},
          theSize{rhs.theSize}
    {
        rhs.head = nullptr;
        rhs.theSize = 0;
    }

    // move assignment
    LinkList &operator=(LinkList &&rhs)
    {
        std::swap(head, rhs.head);
        std::swap(theSize, rhs.theSize);
        return *this;
    }

    // return the size of the linklist
    size_t size()
    {
        return theSize;
    }

    // print the element of the linklist
    void print()
    {
        Node *p = head->next;
        while (p != nullptr)
        {
            std::cout << p->data << " ";
            p = p->next;
        }

        std::cout << std::endl;
    }

    // check that whether val is contained in the linklist.
    bool IsContain(const Comparable &val)
    {
        Node *p = head->next;
        while (p != nullptr)
        {
            if (p->data == val)
                return true;
            p = p->next;
        }
        return false;
    }

    // add element to the linklist.
    // complexity O(N) N is the size of the linklist
    void add(const Comparable &val)
    {
        Node *p = head;
        // traversel to the last element.
        while (p->next != nullptr)
        {
            if(p->next->data == val)
                return;             // the element is already existed.
            else if(p->next->data > val) // search for the lower bound.
                break;
            p = p->next;
        }
        p->next = new Node{val, p->next};
        ++theSize; // increament size.
    }

    // remove element from the linklist.
    // cmplexity O(N).
    void remove(const Comparable &val)
    {
        Node *p = head;
        // traversel to the last element.
        while (p->next != nullptr)
        {
            if (p->next->data == val)
            {
                Node *node = p->next;
                p->next = p->next->next;                
                --theSize; // descreament size.
                delete node;
                break;
            }
            p = p->next;
        }
    }

  private:
    Node *head;
    size_t theSize;

    // init method
    void init()
    {
        head = new Node;
        theSize = 0;
    }
};

int main(int argc, char **argv)
{
    LinkList<int> list;
    for (int i = 0; i < 10; ++i)
        list.add(i*2);

    std::cout << "size of list is " << list.size() << std::endl;
    // test for print.
    list.print();
    // try to add some value.
    list.add(3);
    list.add(11);
    list.remove(2);
    list.remove(6);
    list.add(1);

    list.print();
    std::cout << "size of list is " << list.size() << std::endl;
    std::cout << (list.IsContain(5) ? "Contained 5" : "Not Contained 5");
    std::cout << std::endl;
    return 0;
}