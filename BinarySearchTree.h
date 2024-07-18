#pragma once
#ifndef BINARY_H
#define BINARY_H
#include <iostream>
using namespace std;
template<class ComParable>
class BinarySearchTree
{
public:
	struct BinaryNode {
		ComParable element;
		BinaryNode* left;
		BinaryNode* right;
		
		BinaryNode(const ComParable& theElement, BinaryNode* lt, BinaryNode* rt) :element(theElement), left(lt), right(rt) {};
		BinaryNode(ComParable&& theElement, BinaryNode* lt, BinaryNode* rt) :element(std::move(theElement)), left(lt), right(rt) {};
	};
private:
	BinaryNode* root;

	void insert(const ComParable& x, BinaryNode*& t) {
		if (t == nullptr) {
			t = new BinaryNode{ x,nullptr,nullptr };
		}
		else if (x < t->element) {
			insert(x, t->left);
		}
		else if (t->element < x) {
			insert(x, t->right);
		}
		else
			;
	};
	void insert(ComParable&& x, BinaryNode*& t) {
		if (t == nullptr) {
			t = new BinaryNode{ std::move(x),nullptr,nullptr };
		}
		else if (x < t->element) {
			insert(x, t->left);
		}
		else if (t->element < x) {
			insert(x, t->right);
		}
		else
			;
	};
	void remove(const ComParable& x, BinaryNode*& t) {
		if (t == nullptr) {
			return;
		}
		if (x < t->element) {
			remove(x, t->left);
		}
		else if (t->element < x) {
			remove(x, t->right);
		}
		else if (t->left != nullptr && t->right != nullptr) {
			t->element = findMin(t->right)->eleMent;
			remove(t->element, t->right);
		}
		else {
			BinaryNode* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}
	};
	BinaryNode* findMin(BinaryNode* t) const {
		if (t == nullptr) {
			return nullptr;
		}
		else if (t->left == nullptr) {
			return t;
		}
		else {
			return findMin(t->left);
		}
	}
	BinaryNode* findMax(BinaryNode* t) const {
		if (t != nullptr) {
			while (t->right != nullptr) {
				t = t->right;
			}
		}
		return t;
	}
	bool contains(const ComParable& x, BinaryNode* t) const;
	void makeEmpty(BinaryNode*& t) {
		if (t != nullptr) {
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	};
	void printTree(BinaryNode* t, std::ostream& out) const {
		static int space = 0;
		if (t == nullptr) {
			return;
		}
		else {
			for (int i = 0; i < space; ++i) {
				cout << "\t";
			}
			cout << t->element << endl;
			++space;
			printTree(t->left, out);
			printTree(t->right, out);
			--space;
		}
	};
	BinaryNode* clone(BinaryNode* t) const {
		if (t == nullptr) {
			return nullptr;
		}
		else {
			return new BinaryNode{ t->element,clone(t->left),clone(t->right) };
		}
	};
public:
	BinarySearchTree():root(nullptr){};
	BinarySearchTree(const BinarySearchTree& rhs) :root(nullptr) {
		root = clone(rhs.root);
	};
	BinarySearchTree(BinarySearchTree&& rhs):root(nullptr) {//“∆∂Øππ‘Ï
		root = rhs.root;
		rhs.root = nullptr;
	};
	~BinarySearchTree() {
		makeEmpty(root);
	};

	const ComParable& findMin() const {
		return *findMin(root);
	};
	const ComParable& findMax() const {
		return *findMax(root);
	};
	bool contians(const ComParable& x) const;
	bool isEmpty() const {
		return !root;
	};
	void printTree(ostream& out = cout) const {
		printTree(root, out);
	};

	void makeEmpty() {
		makeEmpty(root);
	};
	void insert(const ComParable& x);
	void insert(ComParable&& x);
	void remove(const ComParable& x);

	BinarySearchTree& operator=(const BinarySearchTree& rhs) {
		makeEmpty(root);
		root = clone(rhs.root);
	};
	BinarySearchTree& operator=(BinarySearchTree&& rhs) {
		makeEmpty(root);
		root = rhs.root;
		rhs.root = nullptr;
	};
};

template<class ComParable>
inline bool BinarySearchTree<ComParable>::contians(const ComParable& x) const
{
	return contains(x,root);
}

template<class ComParable>
inline void BinarySearchTree<ComParable>::insert(const ComParable& x)
{
	insert(x, root);
}

template<class ComParable>
inline void BinarySearchTree<ComParable>::insert(ComParable&& x)
{
	insert(std::move(x), root);
}

template<class ComParable>
inline void BinarySearchTree<ComParable>::remove(const ComParable& x)
{
	remove(x, root);
}

template<class ComParable>
inline bool BinarySearchTree<ComParable>::contains(const ComParable& x, BinaryNode* t) const
{
	if (t == nullptr) {
		return false;
	}
	else if (x < t->element) {
		return contains(x, t->left);
	}
	else if (t->element < x) {
		return contians(x, t->right);
	}
	else {
		return true;
	}
}

#endif