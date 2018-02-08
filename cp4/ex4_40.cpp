/*
 * Exercise 4.40
 * Author: sesiria  2018
 * level-order traversal of the binary Search Tree
 * time complexity O(N)
 */

#include "../Lib/Queue.h"
#include "../Lib/randomize.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

template <typename Comparable>
struct BinaryNode
{
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
        : element{theElement}, left{lt}, right{rt}
    {
    }

    BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
        : element{std::move(theElement)}, left{lt}, right{rt}
    {
    }
};

/**
 * inorder-traversal
 */
template <typename Comparable>
void printTree(BinaryNode<Comparable> *node)
{
    if (node == nullptr)
        return;
    printTree(node->left);
    std::cout << node->element << " ";
    printTree(node->right);
}

/**
 * user preorder traversal to store the node element to two-dimension array.
 * each node is traversal one time. 
 * So with N push_back. + depth times of push_back 
 * so time complexity is O(N + logN) round about O(N)
 * space complexity is O(N + logN) round about O(N)
 */
template <typename Comparable>
void levelOrderTraversalBST(BinaryNode<Comparable> *node, int depth, std::vector<std::vector<Comparable>> &vec)
{
    if (node == nullptr)
        return;

    if (vec.size() <= depth)
        vec.push_back(std::vector<Comparable>{});
    vec[depth].push_back(node->element);

    levelOrderTraversalBST(node->left, depth + 1, vec);
    levelOrderTraversalBST(node->right, depth + 1, vec);
}
/**
 * level-order-traversal of binary search tree
 * time complexity O(N)
 * space complexity O(N)
 * use Extra datastructures. two-dimensional vector.
 */
template <typename Comparable>
void printLevelNodes(BinaryNode<Comparable> *node)
{
    std::vector<std::vector<Comparable>> vec;
    levelOrderTraversalBST(node, 0, vec);

    for (auto &X : vec)
    {
        for (auto &Y : X)
            std::cout << Y << " ";
        std::cout << std::endl;
    }
}

/**
 * level-order-traversal of BST
 * time complexity O(N)
 * space complexity O(N)
 * use extra ds queue.
 */ 
template <typename Comparable>
void printLevelQueue(Queue<BinaryNode<Comparable> *> &queue)
{
    while (!queue.empty())
    {
        BinaryNode<Comparable> *node = queue.dequeue();
        if (node)
            std::cout << node->element << " ";

        if (node->left)
            queue.enqueue(node->left);
        if (node->right)
            queue.enqueue(node->right);
    }
}

/**
 * level-order-traversal of binary search tree
 * time complexity O(N)
 * space complexity O(N)
 * base on the data structure queue
 */
template <typename Comparable>
void printLevelNodes1(BinaryNode<Comparable> *node)
{
    Queue<BinaryNode<Comparable> *> queue;
    queue.enqueue(node);
    printLevelQueue(queue);
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template <typename Comparable>
void insert(const Comparable &x, BinaryNode<Comparable> *&t)
{
    if (t == nullptr)
        t = new BinaryNode<Comparable>{x, nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ; // Duplicate; do nothiing
}

template <typename Comparable>
void makeEmpty(BinaryNode<Comparable> *&t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

/**
 * Fisher-Yaster/Donald.Knuth random shuffle algorithm
 * time complexity O(N)
 */
void shuffleVector(std::vector<int> &ar)
{
    for (int i = 1; i < ar.size(); ++i)
    {
        std::swap(ar[i], ar[randInt(0, i)]);
    }
}

/**
 * generateRandomBST base on the Fisher-Yaster/Donald.Knuth random shuffle algorithm
 * time complexity O(NlogN)
 * space complexity O(N)
 */
template <typename Comparable>
void generateRandomBST(BinaryNode<Comparable> *&t, int nSize)
{
    std::vector<Comparable> vec;
    for (int i = 1; i <= nSize; ++i) // O(N)
        vec.push_back(i);

    shuffleVector(vec); // O(N)

    for (int i = 0; i < vec.size(); ++i) // insert node O(NlogN)
        insert(vec[i], t);
}

int main(int argc, char **argv)
{
    BinaryNode<int> *root = nullptr;
    generateRandomBST(root, 100);
    printLevelNodes(root);
    printLevelNodes1(root);
    return 0;
}
