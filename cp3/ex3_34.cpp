/*
 * Exercise 3.34
 * Author: sesiria  2018
 * determine whether a linklist is a cycle.
 */
#include <iostream>

// ANSI-C style singly-linklist implementation.
struct Node
{
    int data;
    Node *next;
};

// some method for unit test. 
// build the singly-linklist
Node * addNode(Node *node, int data)
{
    return node->next = new Node{data, nullptr};
}

// some method for unit test.
// print linklist.
void printList(Node * first)
{
    Node *p = first;
    while(p != nullptr)
    {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

// destroy the full linklist.
void destroy(Node *first)
{
    Node *p = first;
    while(p->next != nullptr)
    {
        Node *current = p;
        p = p->next;
        delete current;
    }
}

/**
 * determine whether a linklist is cycle.
 * time complexity O(N)
 * space complexity O(1)
 */ 
bool isCycleList(Node * first)
{
    Node *p1 = first;
    Node *p2 = first->next;
    while(p1 != nullptr)
    {
        for (int i = 0; i < 2 && p2 != nullptr; ++i, p2 = p2->next)
            if(p2 == p1) // this is a cycle linklist
                return true;
        p1 = p1->next;
    }
    return false;
}

int
main(int argc, char **argv)
{
    Node *head = new Node{0, nullptr};
    Node *p = head;
    // build linklist.
    for (int i = 1; i < 10; ++i)
        p = addNode(p, i);
    p->next = head; // build and cycle linklist.
    if(isCycleList(head))
        std::cout << "This is a cycle linklist" << std::endl;
    else
        std::cout << "This is not a cycle linklist" << std::endl;
    //printList(head);

    //destroy(head);
    return 0;
}