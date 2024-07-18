#pragma once
#ifndef CIRLIST_H
#define CIRLIST_H

template<class T>
class cirList
{
public:
	struct Node {
		T data;
		Node* next;
	};
private:
	Node* tail;
	unsigned int size;
public:
	cirList() :tail(nullptr), size(0) {};
	~cirList() {
		Node* temp;
		for (int i = 0; i < size; ++i) {
			temp = tail;
			tail = tail->next;
			delete temp;
		}
		tail = nullptr;
		size = 0;
	}

	void push(const T& value) {
		if (tail==nullptr) {
			tail = new Node{ value,nullptr };
			tail->next = tail;
		}
		else {
			Node* p = new Node{ value,tail->next };
			tail->next = p;
			tail = p;
		}
		++size;
	}

	void pop() {
		Node* t = tail->next;
		tail->next = t->next;
		delete t;
		--size;
		if (size == 0) {
			tail = nullptr;
		}
	}

	bool empty() {
		return size == 0;
	}

	const T& top() const {
		return tail->next->data;
	}

};

#endif