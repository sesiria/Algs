/*
 * Exercise 3.36
 * Author: sesiria  2018
 * delete one node of of singly-linklist for specify position.
 * (which is not the header and not the end.)
 */
#include <iostream>
#include <assert.h>

// ANSI-C style singly-linklist implementation.
struct Node
{
    int data;
    Node *next;
};

// some method for unit test.
// build the singly-linklist
Node *addNode(Node *node, int data)
{
    return node->next = new Node{data, nullptr};
}

// some method for unit test.
// print linklist.
void printList(Node *first)
{
    Node *p = first;
    while (p != nullptr)
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
    while (p->next != nullptr)
    {
        Node *current = p;
        p = p->next;
        delete current;
    }
}

/**
 * delete the node of the current position. will not destroy the linklist
 * time complexity O(1)
 */
void deleteNode(Node *node)
{
    assert(node);

    if (node->next)
    {
        node->data = node->next->data;  // copy the value from the next node.
        Node *p = node->next;
        node->next = node->next->next;  // destroy the next node.
        delete p;
    }
    else    // last node of the linklist.
    {
        node->next = nullptr;
    }
}
int main(int argc, char **argv)
{
    Node *head = new Node{0, nullptr};
    Node *p = head;
    Node *itr = nullptr;
    // build linklist.
    for (int i = 1; i < 10; ++i)
    {
        p = addNode(p, i);
        if(i == 5)
            itr = p;
    }
        
    printList(head);
    deleteNode(itr);
    printList(head);
    destroy(head);
    return 0;
}