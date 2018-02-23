/*
 * Ekercise 4.41
 * Author: sesiria  2018
 * A implementation for B-tree(B+tree) including:
 * 1) insertion routine(createTree / search)
 * 2) deletion routine
 * 3) ektended insertion routine
 * time complekity O(N)
 */

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <vector>

template <typename Comparable>
class BTree
{
  private:
    struct TreeNode
    {
        bool isLeaf;
        int numOfKeys;                    // the current size of element in the node/leaf
        std::vector<Comparable> Keys;     // if it is the leaf store the Keys /if it is the nonleaf store the numOfKeys
        std::vector<TreeNode *> children; // store children if it is nonleaf

        TreeNode(bool bLeaf, int theCapacity)
            : isLeaf{bLeaf}, numOfKeys{0}
        {
            if (isLeaf)
            {
                Keys.resize(theCapacity + 1, Comparable{}); // add one more space for split.
            }
            else
            {
                Keys.resize(theCapacity + 1, Comparable{});
                children.resize(theCapacity + 2, nullptr);
            }
        }

        TreeNode(const TreeNode &rhs, TreeNode *pa = nullptr)
            : isLeaf{rhs.isLeaf}, numOfKeys{rhs.numOfKeys}, Keys{rhs.Keys}
        {
            if (isLeaf) // leaf node have nonchildren.
            {
            }
            else // the nonleaf node has M -1 numOfKeys and M linKeys to childrens.
            {
                children.resize(rhs.children.size(), nullptr);
            }
        }
    };

  public:
    BTree(int sizeKeys = 2)
        : root{nullptr}, minDegree{sizeKeys}, maxCounts{minDegree * 2 - 1}
    {
    }

    void insert(const Comparable &k)
    {
        if (root == nullptr)
            createTree();
        
        if (root->numOfKeys == maxCounts) // the root is full we need to increase the height of the B-Tree
        {
            TreeNode *newRoot = new TreeNode{false, maxCounts};
            newRoot->children[0] = root;
            root = newRoot;
            splitChild(root, 0);
        }
        insert(root, k);
    }

    void printTree()
    {
        printTree(root);
        std::cout << std::endl;
    }

  private:
    TreeNode *root;
    const int minDegree; // makimum size of Keys in a TreeNode
    const int maxCounts;

    void insert(TreeNode *t, const Comparable &k)
    {
        if (t == nullptr)
            return;

        int i = t->numOfKeys;
        if (t->isLeaf) // it is an leaf
        {
            while (i >= 1 && k < t->Keys[i - 1])
            {
                std::swap(t->Keys[i], t->Keys[i - 1]);
                --i;
            }
            t->Keys[i] = k;
            t->numOfKeys++;
        }
        else // it is an non-leaf node.
        {
            while (i >= 0 && k < t->Keys[i - 1])
                --i;
            ++i;
            if(t->children[i]->numOfKeys == maxCounts)
            {
                splitChild(t, i);
                if(t->Keys[i] < k)
                    ++i;
            }           
            insert(t->children[i], k);
        }
    }

    std::pair<TreeNode *, int> search(TreeNode *t, const Comparable &k)
    {
        if (t == nullptr)
            return nullptr;

        int i = 0;
        while (i < t->numOfKeys && t->Keys[i] < k)
            ++i;

        if (i < t->numOfKeys && k == t->Keys[i])
            return {t, i};  // the current node contain the k.
        else if (t->isLeaf) // search to the end.
            return nullptr;
        else
            return search(t->childrens[i], k); // the i is always less than the size of the childrens vector.
    }

    void createTree()
    {
        root = new TreeNode{true, maxCounts};
    }

    void printTree(TreeNode *node)
    {
        if (node == nullptr)
            return;

        if (node->isLeaf)
        {
            for (int i = 0; i < node->numOfKeys; ++i)
                std::cout << node->Keys[i] << " ";
        }
        else // print children resursive
        {
            for (int i = 0; i <= node->numOfKeys; ++i)
            {
                printTree(node->children[i]);
                if(i < node->numOfKeys)
                    std::cout << node->Keys[i] << " ";
            }
        }
    }

    // this routine will split the idx-th children node into two children.
    void splitChild(TreeNode *node, int idx)
    {
        TreeNode *nodeChild = node->children[idx];
        TreeNode *nodeNew = new TreeNode{nodeChild->isLeaf, maxCounts};
        nodeNew->numOfKeys = minDegree - 1;

        for (int j = 0; j < minDegree - 1; ++j)
            std::swap(nodeNew->Keys[j], nodeChild->Keys[j + minDegree]);

        if (!nodeChild->isLeaf)
            for (int j = 0; j < minDegree; ++j)
                std::swap(nodeNew->children[j], nodeChild->children[j + minDegree]);

        nodeChild->numOfKeys = minDegree - 1;

        for (int j = node->numOfKeys; j > idx; --j)
            std::swap(node->children[j + 1], node->children[j]);
        node->children[idx + 1] = nodeNew;

        for (int j = node->numOfKeys - 1; j >= idx; --j)
            std::swap(node->Keys[j + 1], node->Keys[j]);

        std::swap(node->Keys[idx], nodeChild->Keys[minDegree - 1]);
        ++node->numOfKeys;
    }
};

int main(int argc, char **argv)
{
    BTree<int> btree{10};
    for (int i = 100; i >= 1; --i)
        btree.insert(i);

    btree.printTree();

    return 0;
}