#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

/*template<class Key>
class hash {
public:
	size_t operator()(const Key& k) const;
};*/


template<>
class hash<string> {
public:
	size_t operator()(const string& k) const {
		size_t hashVal = 0;

		for (char ch : k) {
			hashVal = 37 * hashVal + ch;
		}

		return hashVal;
	};
};

template<class HashedObj>
class HashTable {
public:
	explicit HashTable(int size = 3) :currentSize(0), theLists(size) {};//实际情况用素数

	bool contains(const HashedObj& x) const {
		auto& whichList = theLists[myhash(x)];
		return find(whichList.begin(), whichList.end(), x) != whichList.end();
	};

	void makeEmpty() {
		for (auto& thisList : theLists) {
			thisList.clear();
		}
	};
	bool insert(const HashedObj& x) {
		auto& whichList = theLists[myhash(x)];
		if (find(whichList.begin(), whichList.end(), x) != whichList.end()) {
			return false;
		}
		whichList.push_back(x);

		if (++currentSize > theLists.size() * 0.5) {
			rehash();
		}

		return true;
	};
	bool insert(HashedObj&& x) {
		auto& whichList = theLists[myhash(x)];
		if (find(whichList.begin(), whichList.end(), x) != whichList.end()) {
			return false;
		}
		whichList.push_back(std::move(x));

		if (++currentSize > theLists.size() * 0.5) {
			rehash();
		}

		return true;
	};
	bool remove(const HashedObj& x) {
		auto& whichList = theLists[myhash(x)];
		auto itr = find(whichList.begin(), whichList.end(), x);

		if (itr == whichList.end()) {
			return false;
		}

		whichList.erase(itr);
		--currentSize;
		return true;
	};

	void show() {
		for (auto& i : theLists) {
			for (auto& x : i) {
				cout << x << ' ';
			}
		}
		cout << endl;
	}
private:
	vector<list<HashedObj>> theLists;
	int currentSize;//元素个数

	void rehash(){
		vector<list<HashedObj>> oldLists = theLists;

		theLists.resize(2 * oldLists.size() + 3);//实际情况用素数
		for (auto& thisList : theLists) {
			thisList.clear();
		}
	
		currentSize = 0;
		for (auto& thisList : oldLists) {
			for (auto& x : thisList) {
				insert(std::move(x));
			}
		}
	};
	size_t myhash(const HashedObj& x) const {
		static hash<HashedObj> hf;
		return hf(x) % theLists.size();
	};
};

#endif