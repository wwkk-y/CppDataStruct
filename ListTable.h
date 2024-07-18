#pragma once
#ifndef LISTTABLE_H
#define LISTTABLE_H
#include <list>
#include <vector>
#include <algorithm>
//#include <string>
using namespace std;
template<class T>
class ListTable {
	list<vector<T>> ls;
	int currentSize;

	size_t myhash(const T& value) {
		return hash<T>()(value) % ls.size();
	}
	void rehash() {

	}

public:
	ListTable(int size = 101) :ls(101),currentSize(0) {};

	void insert(const T& value) {
		int pos = myhash(value);
		ls[pos].push_back(value);
		if (++currentSize >= 0.5 * ls.size()) {
			rehash();
		}
	}


	void del(const T& value) {
		int pos = myhash(value);
		ls.erase( find(ls[pos].begin(),ls.[pos].end,value) );
	}

	bool contains(const T& value) {
		int pos = myhash(value);
		if (find(ls[pos].begin(), ls[pos].end(), value) != ls[pos].end()) {
			return true;
		}
		return false;
	}
};
#endif