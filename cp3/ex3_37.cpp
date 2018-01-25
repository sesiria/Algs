/*
 * Exercise 3.37
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
 * remove the node of the current position. will not destroy the linklist
 * time complexity O(1)
 */
void removeNode(Node *node)
{
    assert(node);

    if (node->next)
    {
        node->data = node->next->data;  // copy the value from the next node.
        Node *p = node->next;
        node->next = node->next->next;  // destroy the next node.
        delete p;
    }
    // for a head/tail linklist it is guarantee that the next node will not be nullptr.
    /*else    // last node of the linklist.
    {
        node->next = nullptr;
    }*/
}


/**
 * insert a node before the current node.
 * time complexity O(N)
 */
void insertNode(Node *node, int val) 
{
    assert(node);

    if(node->next)
    {
        node->next = new Node{val, node->next};
        std::swap(node->data, node->next->data);
    }
}


int main(int argc, char **argv)
{
    Node *head = new Node{0, nullptr};
    Node *p = head;
    Node *itr1 = nullptr;
    Node *itr2 = nullptr;
    // build linklist.
    for (int i = 1; i < 10; ++i)
    {
        p = addNode(p, 2 * i);
        if(i == 5)
            itr1 = p;
        if(i == 7)
            itr2 = p;
    }
        
    printList(head);
    insertNode(itr1, 9);
    printList(head);
    removeNode(itr2);
    printList(head);
    destroy(head);
    return 0;
}