/*
 * Ekercise 4.44
 * Author: sesiria  2018
 * traverse a tree with child/sibling links.
 */

#include <iostream>
#include <stack>

// node definition.
template <typename Object>
struct TreeNode
{
    Object data;
    TreeNode *child;
    TreeNode *sibling;
    TreeNode(Object val, TreeNode *ch = nullptr, TreeNode *sb = nullptr)
        : data{val}, child{ch}, sibling{sb}
    {
    }
};

/**
 * traverse a tree with child/sibling links.
 */
template <typename Object>
void traverse(TreeNode<Object> *t)
{
    if (t == nullptr)
        return;

    std::cout << t->data;
    // traverse all children.
    TreeNode<Object> *node = t->child;

    while (node)
    {
        traverse(node);
        node = node->sibling;
    }
}

int main(int argc, char **argv)
{
    TreeNode<char> * node = new TreeNode<char>('J');
    node = new TreeNode<char>('E', node);
    std::stack<TreeNode<char> *> stack;
    stack.push(node);

    node = new TreeNode<char>('I');
    node = new TreeNode<char>('H', nullptr, node);
    node = new TreeNode<char>('D', node, stack.top());
    stack.pop();
    node = new TreeNode<char>('B', node);
    node = new TreeNode<char>('A', node);

    traverse(node);
    return 0;
}