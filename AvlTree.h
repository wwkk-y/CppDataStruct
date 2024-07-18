#pragma once
#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
using namespace std;

template<class Comparable>
class AvlTree
{
public:
	struct AvlNode {
		Comparable element;
		AvlNode* left;
		AvlNode* right;
		//int height;

		AvlNode(const Comparable& ele, AvlNode* lt, AvlNode* rt) 
				:element(ele), left(lt), right(rt) {};
		AvlNode(Comparable&& ele, AvlNode* lt, AvlNode* rt) 
				:element(std::move(ele)), left(lt), right(rt) {};
	};
private:
	AvlNode* root = nullptr;

	static const int ALLOWED_IMBALANCE = 1;

	AvlNode* findMin(AvlNode* t) const {
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
	AvlNode* findMax(AvlNode* t) const {
		if (t != nullptr) {
			while (t->right != nullptr) {
				t = t->right;
			}
		}
		return t;
	}

	int max(int t1, int t2) {
		return t1 > t2 ? t1 : t2;
	}

	int height(AvlNode* t) {
		if (t == nullptr) {
			return -1;
		}
		else {
			return max( height(t->left), height(t->right) ) + 1;
		}
	}

	void rotateWithLeftChild(AvlNode*& k2) {
		AvlNode* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;

		//k2->height = max(height(k2->left), height(k2->right)) + 1;
		//k1->height = max(height(k1->left), height(k1->right)) + 1;

		k2 = k1;
	}

	void rotateWithRightChild(AvlNode*& k2) {
		AvlNode* k1 = k2->right;
		k2->right = k1->left;
		k1->left = k2;

		//k2->height = max(height(k2->left), height(k2->right)) + 1;
		//k1->height = max(height(k1->left), height(k1->right)) + 1;

		k2 = k1;
	}

	void doubleWithLeftChild(AvlNode*& k3) {
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}

	void doubleWithRightChild(AvlNode*& k3) {
		rotateWithLeftChild(k3->right);
		rotateWithRightChild(k3);
	}

	void balance(AvlNode*& t) {
		if (t == nullptr) {
			return;
		}
		else if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
			if (height(t->left->left) >= height(t->left->right)) {
				rotateWithLeftChild(t);
			}
			else {
				doubleWithLeftChild(t);
			}
		}
		else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
			if (height(t->right->right) >= height(t->right->left)) {
				rotateWithRightChild(t);
			}
			else {
				doubleWithRightChild(t);
			}
		}

		//t->height = max(height(t->left), height(t->right)) + 1;
	}

	void insert(const Comparable& x, AvlNode*& t) {
		if (t == nullptr) {
			t = new AvlNode{ x,nullptr,nullptr };
		}
		else if (x < t->element) {
			insert(x, t->left);
		}
		else if(t->element < x) {
			insert(x, t->right);
		}

		balance(t);
	}

	void insertFast(const Comparable& x, AvlNode*& t) {
		if (t == nullptr) {
			t = new AvlNode(x, nullptr, nullptr);
			return;
		}
		AvlNode* p = t;
		while (1) {
			if (x < p->element) {
				if (p->left == nullptr) {
					p->left = new AvlNode(x, nullptr, nullptr);
					break;
				}
				p = p->left;
			}
			else if (p->element < x) {
				if (p->right == nullptr) {
					p->right = new AvlNode(x, nullptr, nullptr);
					break;
				}
				p = p->right;
			}
			else {
				break;
			}
		}
	}

	void show(AvlNode*& t) {
		static int space = 0;
		if (t == nullptr) {
			cout<< endl;
			return;
		}

		++space;
		show(t->left);
		--space;

		for (int i = 0; i < space; ++i) {
			cout << "    ";
		}
		cout << t->element << endl;
		
		++space;
		show(t->right);
		--space;
	}

	void remove(const Comparable& x, AvlNode*& t) {
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
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else {
			AvlNode* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}

		balance(t);
	}
	void printTree(AvlNode* p) {
		if (p == nullptr) {
			return;
		}
		printTree(p->left);
		cout << p->element << ' ';
		printTree(p->right);
	}

public:
	void show() { show(root); }
	void insert(const Comparable& value) { insert(value, root); }
	void insertFast(const Comparable& value) { insertFast(value, root); }
	void printTree() { printTree(root); std::cout << std::endl; }
};

#endif