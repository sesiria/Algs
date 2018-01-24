/*
 * Exercise 3.30
 * Author: sesiria  2018
 * Implementation for self-adjusting list
 * a) array implementation
 * b) linklist implementation
 */
#include <iostream>
#include <vector>

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
 * ansi-c style implementation of linklist of self-adjusting list
 * time complexity O(N) worst case for search the node.
 * the adjustment time complexity is O(1)
 */ 
bool findLinkList(Node ** list, int x)
{
    Node *p = *list;
    Node *prev = nullptr;
    while(p != nullptr)
    {
        if(p->data == x)
            break;
        prev = p;
        p = p->next;
    }

    if(p != nullptr) // we found the node
    {
        if(prev != nullptr) // p is not the fist node
        {
            prev->next = p->next;
            p->next = *list;
            *list = p;      // change the header.
        }
        // if p is the first node we don't need to do anything.
        return true;
    }
    return false;
}

/**
 * Implementation for Array style self-adjusting list
 * time complexity O(N)
 */ 
template <typename Object>
bool findArray(std::vector<Object> & list, const Object & x)
{
    if(list.empty())
        return false;
    int pos = list.size() - 1;
    for (; pos >= 0; pos--)
    {
        if(list[pos] == x)
            break;
    }
    if(pos < 0)
        return false;

    for (int i = pos; i < list.size() - 1; ++i)
        list[i] = list[i + 1];
    list[list.size() - 1] = x;
    return true;
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

    findLinkList(&head, 3);
    findLinkList(&head, 7);
    findLinkList(&head, 9);
    findLinkList(&head, 9);
    printList(head);

    destroy(head);

    // test for array self-adjusting list
    std::vector<int> list = {0, 1, 2, 3, 4, 5, 6, 7, 9, 8};
    findArray(list, 2);
    findArray(list, 4);
    findArray(list, 7);
    for(auto &x : list)
        std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}