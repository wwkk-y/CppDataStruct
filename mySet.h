#pragma once
#ifndef MYSET_H
#define MYSET_H
#include <iostream>
template<class T>
class MySet
{
public:
	struct Node {
		T data;
		Node* left;
		Node* right;
		Node* front;
		Node(const T& data, Node* left = nullptr, Node* right = nullptr, Node* front = nullptr)
			:data(data), left(left), right(right), front(front) {};
		Node(T&& data, Node* left = nullptr, Node* right = nullptr, Node* front = nullptr)
			:data(std::move(data)), left(left), right(right), front(front) {};
	};

	class iterator {
		Node* current;
		iterator(Node* current) :current(current) {};
		friend class MySet;
	public:
		iterator& operator++() {//不检查越界行为
			//有右节点
			if (current->right != nullptr) {
				current = findMin(current);
			}
			//没有右节点
			else {
				Node* front = current->front;
				//是父节点的左节点
				if (current == front->left) {
					current = front;
				}
				//是父节点的右节点
				else {
					current = front->front;
				}
			}
			return *this;
		}

		T& operator*() {
			return current->data;
		}
	};

private:
	Node* root;
	
	void insert(const T& value, Node*& p,Node* front=nullptr) {
		if (p == nullptr) {
			p = new Node(value);//指向父节点?
			p->front = front;
		}
		else if (value < p->data) {
			insert(value, p->left, p);
		}
		else if (p->data < value) {
			insert(value, p->right, p);
		}
	}
	void insert(T&& value, Node*& p,Node* front = nullptr) {
		if (p == nullptr) {
			p = new Node(std::move(value));//指向父节点?
			p->front = front;
		}
		else if (value < p->data) {
			insert(value, p->left, p);
		}
		else if (p->data < value) {
			insert(value, p->right, p);
		}
	}

	Node* findMin(Node* p) {
		if (p == nullptr) {
			throw;
		}

		if (p->left == nullptr) {
			return p;
		}
		else {
			return findMin(p->left);
		}
	}

	void move(const T& value,Node*& p) {
		if (p == nullptr) {
			return;
		}

		if (value < p->data) {
			move(value, p->left);
		}
		else if (p->data < value) {
			move(value, p->right);
		}
		else{
			//只有一个子节点或者没有子节点
			if (p->left == nullptr || p->right == nullptr) {
				Node* temp = p;
				p = (p->left != nullptr) ? p->left : p->right;
				if (p != nullptr) {
					p->front = temp->front;
				}

				delete temp;
			}
			//有两个子节点
			else {
				p->data = findMin(p->right)->data;
				move(p->data, p->right);
			}
		}
	}

	iterator find(const T& value, Node* p) {
		if (p == nullptr) {
			return iterator(nullptr);
		}

		if (value < p->data) {
			return find(value, p->left);
		}
		else if (p->data < value) {
			return find(value, p->right);
		}
		else {
			return iterator(p);
		}
	}

	void clear(Node* p) {
		if (p == nullptr) {
			return;
		}
		clear(p->left);
		clear(p->right);
		delete p;
	}

	Node* clone(Node* p) {
		if (p == nullptr) {
			return nullptr;
		}
		Node* temp = new Node(p->data, clone(p->left), clone(p->right));
		
		if (p->left) {
			Node*& left = temp->left;
			left->front = temp;
		}
		
		if (p->right) {
			Node*& right = temp->right;
			right->front = temp;
		}

		return temp;
	}
	void show(Node* p) {
		using namespace std;
		static int space = 0;
		if (p == nullptr) {
			cout << endl;
			return;
		}

		++space;
		show(p->left);
		--space;
		
		for (int i = 0; i < space; ++i) {
			cout << "    ";
		}
		cout << p->data << endl;

		++space;
		show(p->right);
		--space;
	}
public:
	MySet() :root(nullptr){};
	MySet& operator=(const MySet& rhs) { 
		clear(root); 
		root = clone(rhs.root); 
		return *this;
	};
	MySet& operator=(MySet&& rhs) {
		root = rhs.root;
		rhs.root = nullptr;
		return *this;
	}

	MySet(const MySet& rhs){ root = clone(rhs.root); };
	MySet(MySet&& rhs) { root = rhs.root; rhs.root = nullptr; }

	~MySet() { clear(); }
	
	void insert(const T& value) { insert(value, root); }
	void insert(T&& value) { insert(std::move(value), root); }

	void move(const T& value) { move(value, root); }
	iterator find(const T& value) { return find(value, root); }
	void clear() { clear(root); root = nullptr; }

	void show() { show(root); }
};
#endif
