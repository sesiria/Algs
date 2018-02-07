/*
 * Exercise 4.31
 * Author: sesiria  2018
 * Algorithm to calculate the:
 * 1) nodes of a Tree T
 * 2) leaves of a Tree T
 * 3) full nodes of a Tree T.
 */

#include <algorithm>
#include <iostream>
#include <ostream>
#include <stack>

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
 * Count the number of nodes of a binaryTree.
 * complexity O(N)
 */
template <typename Comparable>
int countNodes(BinaryNode<Comparable> *node)
{
    if (node == nullptr)
        return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

/**
 * Count the number of leaves of a binaryTree.
 * the number full nodes + 1 = number of leaves.
 * complexity O(N)
 */
template <typename Comparable>
int countLeaves(BinaryNode<Comparable> *node)
{
    if (node == nullptr)
        return 0;
    int leafCount = (node->left == nullptr &&node->right == nullptr) ? 1 : 0;
    return leafCount + countLeaves(node->left) + countLeaves(node->right);
}

/**
 * Count the number of full nodes of a binaryTree.
 * the number full nodes + 1 = number of leaves.
 * complexity O(N) 
 */
template <typename Comparable>
int countFullNodes(BinaryNode<Comparable> *node)
{
    if (node == nullptr)
        return 0;
    int fullNodeCount = (node->left && node->right) ? 1 : 0;
    return fullNodeCount + countFullNodes(node->left) + countFullNodes(node->right);
}

template <typename Comparable>
void printTree(BinaryNode<Comparable> *node)
{
    if (node == nullptr)
        return;
    bool bBrace = false;
    if (node->left || node->right)
        bBrace = true;
    if (bBrace)
        std::cout << "(";
    printTree(node->left);
    std::cout << node->element;
    printTree(node->right);

    if (bBrace)
        std::cout << ")";
}

int main(int argc, char **argv)
{
    // build the test case tree.
    // build the left subtree.
    std::stack<BinaryNode<char> *> stack;
    BinaryNode<char> *left = new BinaryNode<char>{'b', nullptr, nullptr};
    BinaryNode<char> *right = new BinaryNode<char>{'c', nullptr, nullptr};
    BinaryNode<char> *node = new BinaryNode<char>{'*', left, right};
    left = new BinaryNode<char>{'a', nullptr, nullptr};
    right = node;
    node = new BinaryNode<char>{'+', left, right};
    stack.push(node);

    // build the right subtree.
    left = new BinaryNode<char>{'d', nullptr, nullptr};
    right = new BinaryNode<char>{'e', nullptr, nullptr};
    node = new BinaryNode<char>{'*', left, right};
    right = new BinaryNode<char>{'f', nullptr, nullptr};
    left = node;
    node = new BinaryNode<char>{'+', left, right};
    left = node;
    right = new BinaryNode<char>{'g', nullptr, nullptr};
    node = new BinaryNode<char>{'*', left, right};
    left = stack.top();
    stack.pop();
    right = node;
    node = new BinaryNode<char>{'+', left, right};

    printTree(node);
    std::cout << std::endl;
    std::cout << countNodes(node) << std::endl;
    std::cout << countLeaves(node) << std::endl;
    std::cout << countFullNodes(node) << std::endl;
    return 0;
}
