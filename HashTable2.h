#pragma once
#ifndef HASHMAP_2_H
#define HASHMAP_2_H
#include "HashTable.h"
#include <iostream>
#include <vector>
using namespace std;
template<class HashedObj>
class HashTable2 {
public:
	explicit HashTable2(int size = 3) :array(size),currentSize(0){};//实际情况使用素数

	bool contains(const HashedObj& x) const {
		return isAlive(findPos(x));
	};

	void makeEmpty() {
		currentSize = 0;
		for (HashEntry& entry : array) {
			entry.info = EMPTY;
		}
	};
	bool insert(const HashedObj& x) {
		int currentPos = findPos(x);
		if (isActive(currentPos)) {
			return false;
		}

		array[currentPos].element = x;
		array[currentPos].info = ACTIVE;

		if (++currentSize >= array.size() * 0.5) {
			rehash();
		}

		return true;
	};
	bool insert(HashedObj&& x) {
		int currentPos = findPos(x);
		if (isActive(currentPos)) {
			return false;
		}

		array[currentPos].element = std::move(x);
		array[currentPos].info = ACTIVE;

		if (++currentSize >= array.size() * 0.5) {
			rehash();
		}

		return true;
	};
	bool remove(const HashedObj& x) {
		int currentPos = findPos(x);
		if (!isActive(currentPos)) {
			return false;
		}
		
		array[currentPos].info = DELETED;
		return true;
	};
	void show() {
		for (auto& i : array) {
			if (i.info == ACTIVE) {
				cout << i.element << ' ';
			}
		}
		cout << endl;
	}

	enum EntryType{ACTIVE,EMPTY,DELETED};
private:
	struct HashEntry {
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj& e=HashedObj(), EntryType i = EMPTY) :element(e), info(i) {};
		HashEntry(HashedObj&& e, EntryType i = EMPTY) :element(std::move(e)), info(i) {};
	};
	vector<HashEntry> array;
	int currentSize;

	bool isActive(int currentPos) const {
		return array[currentPos].info == ACTIVE;
	};
	int findPos(const HashedObj& x) const {
		int offset = 1;
		int currentPos = myhash(x);

		while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
			currentPos += offset;
			offset += 2;
			if (currentPos >= array.size())
				currentPos -= array.size();
		}

		return currentPos;
	};
	void rehash(){
		vector<HashEntry> oldArray = array;

		array.resize(2 * oldArray.size() + 3);//实际情况用素数
		for (auto& entry : array) {
			entry.info = EMPTY;
		}
		currentSize = 0;
		for (auto& entry : oldArray) {
			if (entry.info == ACTIVE) {
				insert(std::move(entry.element));
			}
		}
	};

	size_t myhash(const HashedObj& x) const{ 
		static hash<HashedObj> hf;
		return hf(x) % array.size();
	};
};
#endif