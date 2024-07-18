#pragma once
#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <vector>
using namespace std;
template<class T>
class myQueue
{
	vector<T> v;
	int head;
	int tail;
public:
	myQueue(int size = 16) :v(size),head(0),tail(-1) {};
	void push(const T& value) {
		if (tail == v.size()-1) {
			v[tail=0] = value;
		}
		else {
			v[++tail] = value;
		}
	}

	void pop() {
		if (head == v.size() - 1) {
			head = 0;
		}
		else {
			++head;
		}
	}
	const T& top() const {
		return v[head];
	}

	bool empty() {
		return tail == head - 1;
	}
};

#endif