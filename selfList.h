#pragma once
#ifndef SELFLIST_H
#define SELFLIST_H
#include <list>

using namespace std;
template<class T>
class selfListArr
{
	T arr[16];
	int head;
public:
	selfListArr() :head(16) {};
	void insert(const T& value) {
		arr[--head] = value;
	}
	bool empty() {
		return head == 16;
	}
	bool find(const T& value) {
		for (int i = head; i < 16; ++i) {
			if (arr[i] == value) {
				
				int temp = arr[i];
				arr[i] = arr[head];
				arr[head] = temp;

				return true;
			}
		}
		return false;
	}
	const T& top() const {
		return arr[head];
	}
};

template<class T>
class selfList {
	list<T> ls;
public:
	void insert(const T& value) {
		ls.push_front(value);
	}
	bool empty() {
		return ls.empty();
	}
	bool find(const T& value) {
		list<int>::iterator it = std::find(ls.begin(), ls.end(), value);
		if (it == ls.end()) {
			return false;
		}
		ls.erase(it);
		ls.push_front(value);
		return true;
	}
	const T& top() const {
		return ls.front();
	}
};

#endif