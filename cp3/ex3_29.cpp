/*
 * Exercise 3.29
 * Author: sesiria  2018
 * reversal singly linked list, using only constant extra space.
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
 * assume no header. Reverse the linklist.
 * time complexity O(N)
 * space complexity O(1)
 */ 
Node * reverse(Node * first)
{
    Node *p = first;
    Node *prev = nullptr;
    Node *next = nullptr;
    while(p != nullptr)
    {
        next = p->next;         // save the next node at first.
        p->next = prev;         // relink the current node to previous one
        prev = p;               // save the previous one to current.
        p = next;               // navigate to the next node.
    }
    return prev;                // return the previous one which is the new header.
}

int
main(int argc, char **argv)
{
    Node *head = new Node{0, nullptr};
    Node *p = head;
    // build linklist.
    for (int i = 1; i < 10; ++i)
        p = addNode(p, i);
    printList(head);

    // reverse the linklist
    head = reverse(head);
    printList(head);

    destroy(head);
    return 0;
}