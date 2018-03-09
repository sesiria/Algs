/*
 * Ekercise 4.41
 * Author: sesiria  2018
 * A implementation for B-tree(B+tree) including:
 * 1) insertion routine(createTree / search)
 * 2) deletion routine
 * 3) extended insertion routine
 * time complekity O(N)
 * Refer Introduction to Algorithm 3rd Chapter 18 B-Trees.
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

    void remove(const Comparable &k)
    {
        if (root == nullptr)
            return;

        if (root->numOfKeys == 0) // shrink the B-Tree
        {
            TreeNode *oldRoot = root;
            root = root->children[0];
            delete oldRoot;
        }
        remove(root, k);
    }

    bool search(const Comparable &k)
    {
        return search(root, k).first != nullptr;
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
            if (t->children[i]->numOfKeys == maxCounts)
            {
                splitChild(t, i);
                if (t->Keys[i] < k)
                    ++i;
            }
            insert(t->children[i], k);
        }
    }

    // remove the node which is legal.
    void remove(TreeNode *t, const Comparable &k)
    {
        if (t == nullptr)
            return;

        int i = 0;
        // search for the Keys
        while (i < t->numOfKeys && t->Keys[i] < k)
            ++i;
        if (t->isLeaf)
        {
            if (i < t->numOfKeys && t->Keys[i] == k) // match the Keys
            {
                Comparable blankValue{};
                std::swap(t->Keys[i], blankValue); // remove the Keys
                // rearrange the Keys.
                for (int j = i + 1; j < t->numOfKeys; ++j)
                    std::swap(t->Keys[j - 1], t->Keys[j]);
                --t->numOfKeys;
            }
        }
        else // it is an internal node.
        {
            if (i < t->numOfKeys && t->Keys[i] == k) // match the Keys within the internal node
            {
                if (t->children[i]->numOfKeys >= minDegree) // case 2-a
                {
                    TreeNode *nodeChild = t->children[i];
                    t->Keys[i] = findMaxKey(nodeChild); //nodeChild->Keys[nodeChild->numOfKeys - 1];
                    remove(nodeChild, t->Keys[i]);
                }
                else if (t->children[i + 1]->numOfKeys >= minDegree) // case 2-b
                {
                    TreeNode *nodeChild = t->children[i + 1];
                    t->Keys[i] = findMinKey(nodeChild); //nodeChild->Keys[0];
                    remove(nodeChild, t->Keys[i]);
                }
                else // case 2-c
                {
                    mergeChild(t, i);
                    remove(t->children[i], k);
                }
            }
            else
            {
                // determine the sibling.
                if (t->children[i]->numOfKeys == minDegree - 1)
                {
                    int sibidx = i;
                    if (i == 0)
                        sibidx = i + 1;
                    else if (i == t->numOfKeys)
                        sibidx = i - 1;
                    else
                        sibidx = (t->children[i - 1]->numOfKeys > minDegree - 1) ? i - 1 : i + 1;

                    if (t->children[sibidx]->numOfKeys >= minDegree) // case 3a
                    {
                        if (sibidx > i)
                            exchangeRightSibling(t, i); // arrange right sibling
                        else
                            exchangeLeftSibling(t, sibidx); // arrange left sibling
                    }
                    else // case 3b
                    {
                        if (sibidx > i)
                            mergeChild(t, i); // merge with right sibling
                        else
                            mergeChild(t, --i); // merge with left sibling
                    }
                }
                remove(t->children[i], k);
            }
        }
    }

    std::pair<TreeNode *, int> search(TreeNode *t, const Comparable &k)
    {
        if (t == nullptr)
            return {nullptr, -1};

        int i = 0;
        while (i < t->numOfKeys && t->Keys[i] < k)
            ++i;

        if (i < t->numOfKeys && k == t->Keys[i])
            return {t, i};  // the current node contain the k.
        else if (t->isLeaf) // search to the end.
            return {nullptr, -1};
        else
            return search(t->children[i], k); // the i is always less than the size of the childrens vector.
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
                if (i < node->numOfKeys)
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

    // this routine will down the current Keys and merge
    // the left and right child of the node into one child.
    void mergeChild(TreeNode *node, int idx)
    {
        TreeNode *nodechild1 = node->children[idx];
        TreeNode *nodechild2 = node->children[idx + 1];

        // 1. merge all Keys and children to nodechild1.
        // add Keys from current node.
        std::swap(nodechild1->Keys[nodechild1->numOfKeys], node->Keys[idx]);
        // add Keys from child2.
        for (int i = nodechild1->numOfKeys + 1, j = 0; j < nodechild2->numOfKeys; ++i, ++j)
            std::swap(nodechild1->Keys[i], nodechild2->Keys[j]);

        // copy children from nodechild2 to nodechild1.
        if (!nodechild1->isLeaf)
            for (int i = nodechild1->numOfKeys + 1, j = 0; j <= nodechild2->numOfKeys; ++i, ++j)
                std::swap(nodechild1->children[i], nodechild2->children[j]);

        nodechild1->numOfKeys += 1 + nodechild2->numOfKeys;
        // 2. delete idx-Keys and child2 .
        delete node->children[idx + 1];
        node->children[idx + 1] = nullptr;

        // arrange Keys of the node.
        for (int j = idx + 1; j < node->numOfKeys; ++j)
            std::swap(node->Keys[j - 1], node->Keys[j]);

        // arrange child after child2.
        for (int j = idx + 2; j <= node->numOfKeys; ++j)
            std::swap(node->children[j - 1], node->children[j]);
        --node->numOfKeys;
    }

    void exchangeLeftSibling(TreeNode *t, int idx)
    {
        TreeNode *nodeSibling = t->children[idx];
        TreeNode *nodeChild = t->children[idx + 1];

        // rearrange nodechild first
        for (int i = nodeChild->numOfKeys - 1; i >= 0; --i)
            std::swap(nodeChild->Keys[i], nodeChild->Keys[i + 1]);

        if (!nodeChild->isLeaf)
            for (int i = nodeChild->numOfKeys; i >= 0; --i)
                std::swap(nodeChild->children[i], nodeChild->children[i + 1]);
        ++nodeChild->numOfKeys;

        // swap Keys & child.
        std::swap(nodeChild->Keys[0], t->Keys[idx]);
        std::swap(t->Keys[idx], nodeSibling->Keys[nodeSibling->numOfKeys - 1]);
        if (!nodeChild->isLeaf)
            std::swap(nodeChild->children[0], nodeSibling->children[nodeSibling->numOfKeys]);
        --nodeSibling->numOfKeys;
    }

    void exchangeRightSibling(TreeNode *t, int idx)
    {
        TreeNode *nodeChild = t->children[idx];
        TreeNode *nodeSibling = t->children[idx + 1];

        // down the current Keys
        std::swap(nodeChild->Keys[nodeChild->numOfKeys++], t->Keys[idx]);
        if (!nodeSibling->isLeaf)
            std::swap(nodeChild->children[nodeChild->numOfKeys], nodeSibling->children[0]);
        std::swap(t->Keys[idx], nodeSibling->Keys[0]);

        // rearrange the sibling Keys and children
        for (int i = 1; i < nodeSibling->numOfKeys; ++i)
            std::swap(nodeSibling->Keys[i - 1], nodeSibling->Keys[i]);

        if (!nodeSibling->isLeaf)
            for (int i = 1; i <= nodeSibling->numOfKeys; ++i)
                std::swap(nodeSibling->children[i - 1], nodeSibling->children[i]);
        --nodeSibling->numOfKeys;
    }

    Comparable findMaxKey(TreeNode *t)
    {
        if(t->isLeaf)
            return t->Keys[t->numOfKeys - 1];
        else
            return findMaxKey(t->children[t->numOfKeys]);
    }

    Comparable findMinKey(TreeNode *t)
    {
        if(t->isLeaf)
            return t->Keys[0];
        else
            return findMaxKey(t->children[0]);
    }
};

int main(int argc, char **argv)
{
    BTree<int> btree{5};
    for (int i = 100; i >= 1; --i)
        btree.insert(i);

    btree.printTree();

   for (int i = 1; i * 2 <= 100; ++i)
        btree.remove(i * 2);

    btree.printTree();

    for (int i = 1; i  < 100; ++i)
    {
        btree.remove(i);
    }
        
    btree.printTree();

    return 0;
}
