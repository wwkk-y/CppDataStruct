#pragma once
#ifndef BINOMIALQUEUE_H
#define BINOMIALQUEUE_H
#include <vector>
using namespace std;
template<class Comparable>
class BinomialQueue {
public:
	BinomialQueue();
	BinomialQueue(const Comparable& item);
	BinomialQueue(const BinomialQueue& rhs);
	BinomialQueue(BinomialQueue&& rhs);

	~BinomialQueue();

	BinomialQueue& operator=(const BinomialQueue& rhs);
	BinomialQueue& operator=(BinomialQueue&& rhs);

	bool isEmpty() const;
	const Comparable& findMin() const;

	void insert(const Comparable& x);
	void insert(Comparable&& x);
	void deleteMin();
	void deleteMin(Comparable& minItem);

	void makeEmpty();
	void merge(BinomialQueue& rhs) {
		if (this == &rhs) return;

		currentSize += rhs.currentSize;
		if (currentSize > capacity()) {
			int oldNumTrees = theTrees.size();
			int newNumTrees = max(theTrees.size(), rhs.theTrees.size()) + 1;//?
			theTrees.resize(newNumTrees);
			for (int i = oldNumTrees; i < newNumTrees; ++i) {
				theTrees[i] = nullptr;
			}
		}
		BinomialNode* carry = nullptr;
		for (int i = 0, j = 1; j <= currentSize; ++i, j *= 2) {
			BinomialNode* t1 = theTrees[i];
			BinomialNode* t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;

			int whichCase = t1 = nullptr ? 0 : 1;
			whichCase += t2 == nullptr ? 0 : 2;
			whichCase += carry == nullptr ? 0 : 4;

			switch (whichCase) {
			case 0:
			case 1:
				break;
			case 2:
				theTrees[i] = t2;
				rhs.theTrees[i] = nullptr;
				break;
			case 4:
				theTrees[i] = carry;
				carry = nullptr;
				break;
			case 3:

			}
		}
	};

private:
	struct BinomialNode {
		Comparable element;
		BinomialNode* leftChild;
		BinomialNode* nextSibling;

		BinomialNode(const Comparable& e, BinomialNode* lt, BinomialNode* rt)
			:element(e), leftChild(lt), nextSibling(rt) {};
		BinomialNode(Comparable&& e, BinomialNode* lt, BinomialNode* rt)
			:element(std::move(e)), leftChild(lt), nextSibling(rt) {};
	};

	const static int DEFAULT_TREES = 1;

	vector<BinomialNode*> theTrees;
	int currentSize;

	int findMinIndex() const;
	int capacity() const;
	BinomialNode* combineTrees(BinomialNode* t1, BinomialNode* t2) {
		if (t2->element < t1->element)
			return combineTrees(t2, t1);
		t2->nextSibling = t1->leftChild;
		t1->leftChild = t2;
		return t1;
	}
	void makeEmpty(BinomialNode*& t);
	BinomialNode* clone(BinomialNode* t) const;
};
#endif BINOMIALQUEUE_H