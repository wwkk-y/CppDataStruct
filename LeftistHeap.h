#pragma once
#ifndef LEFTISTHEAP
#define LEFTISTHEAP
template <class Comparable>
class LeftistHeap {
public:
	LeftistHeap();
	LeftistHeap(const LeftistHeap& rhs);
	LeftistHeap(LeftistHeap&& rhs);

	~LeftistHeap();

	LeftistHeap& operator=(const LeftistHeap& rhs);
	LeftistHeap& operator=(LeftistHeap&& rhs);

	bool isEmpty() const;
	const Comparable& findMin() const;

	void insert(const Comparable& x) {
		root = merge(new LeftistNode(x), root);
	};
	void insert(Comparable&& x) {
		root = merge(new LeftistNode{ std::move(x) },root);
	};

	void deleteMin() {
		if (isEmpty()) {
			throw "Empty";
		}

		LeftistNode* oldRoot = root;
		root = merge(root->left, root->right);
		delete oldRoot;
	}

	void deleteMin(Comparable& minItem) {
		minItem = finMin();
		deleteMin();
	};
	void makeEmpty();
	void merge(LeftistHeap& rhs) {
		if (this == &rhs) return;
		root = merge(root, rhs.root);
		rhs.root = nullptr;
	};

private:
	struct LeftistNode {
		Comparable element;
		LeftistNode* left;
		LeftistNode* right;
		int npl;

		LeftistNode(const Comparable& e, LeftistNode* lt = nullptr, LeftistNode* rt = nullptr, int np = 0)
			:element(e), left(lt), right(rt), npl(np) {};
		LeftistNode(Comparable&& e,LeftistNode* lt=nullptr, eftistNode* rt = nullptr, int np = 0)
			:element(std::move(e)), left(lt), right(rt), npl(np) {};
	};

	LeftistNode* root;
	LeftistNode* merge(LeftistNode* h1, LeftistNode* h2) {
		if (h1 == nullptr) return h2;
		if (h2 == nullptr) return h1;
		if (h1->element < h2->element) return mergel(h1, h2);
		else return mergel(h2, h1);

	};
	LeftistNode* mergel(LeftistNode* h1, LeftistNode* h2) {
		if (h1->left == nullptr) h1->left = h2;
		else {
			h1->right = merge(h1->right, h2);
			if (h1->left->npl < h1->right->npl) {
				swapChildren(h1);
			}
			h1->npl = h1->right->npl + 1;
		}
		return h1;
	};

	void swapChildren(LeftistNode* t) {
		LeftistNode* temp = t->right;
		t->left = t->right;
		t->right = temp;
	};
	void reclaimMemory(LeftistNode* t);
	LeftistNode* clone(LeftistNode* t) const;
};
#endif