#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

#include <algorithm>
#include <vector>

template <typename Comparable>
class BinomialQueue
{
  public:
    BinomialQueue();
    BinomialQueue(const Comparable &item);
    BinomialQueue(BinomialQueue &&rhs);

    ~BinomialQueue();

    BinomialQueue &operator=(const BinomialQueue &rhs);
    BinomialQueue &operator=(BinomialQueue &&rhs);

    bool isEmpty() const;
    const Comparable &findMin() const;

    void insert(const Comparable &x);
    void insert(Comparable &&x);
    void deleteMin();
    void deleteMin(Comparable &minItem);

    void makeEmpty();
    void merge(BinomialQueue &rhs);

  private:
    struct BinomialNode
    {
        Comparable element;
        BinomialNode *leftChild;
        BinomialNode *nextSibling;

        BinomialNode(const Comparable &e, BinomialNode *lt, BinomialNode *rt)
            : element{e}, leftChild{lt}, nextSibling{rt} {}

        BinomialNode(Comparable &&e, BinomialNode *lt, BinomialNode *rt)
            : element{std::move(e)}, leftChild{lt}, nextSibling{rt} {}
    };

    constexpr static int DEFAULT_TREES = 1;

    std::vector<BinomialNode *> theTrees; // An array of tree roots
    int currentSize;                      // Number of items in the priority queue

    int findMinIndex() const;
    int capacity() const;
    BinomialNode *combineTrees(BinomialNode *t1, BinomialNode *t2);
    void makeEmpty(BinomialNode *&t);
    BinomialNode *clone(BinomialNode *t) const;
};

#endif