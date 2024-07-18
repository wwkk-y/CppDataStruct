#pragma once
#ifndef CUCKOOHASHTABLE_H
#define CUCKOOHASHTABLE_H
#include <vector>
using namespace std;

template<class AnyType>
class CuckooHashFamily {
public:
	size_t hash(const AnyType& x, int which) const;
	int getNumberOfFunctions();
	void generateNewFunctions();
};

#include <time.h>
class UniformRandom {//获取随机数
	int current;
public:
	UniformRandom() { 
		srand((unsigned)time(nullptr));
		current = 0;
	}
	int operator()(int limit) {
		return rand() % limit;
	}
	int nextInt(int limit) { 
		if (++current > limit) {
			current = 1;
		}
		return current;
	}
	int nextInt() { return ++current; }
};

template<class AnyType,class HashFamily>
class CuckooHashTable {
	struct HashEntry {
		AnyType element;
		bool isActive;

		HashEntry(const AnyType& e = AnyType(), bool a = false)
			:element(e), isActive(a) {};
		HashEntry(AnyType&& e, bool a = false)
			:element(std::move(e)), isActive(a) {};
	};

	static const double MAX_LOAD = 0.40;
	static const int ALLOWED_REHASHES = 5;

	vector<HashEntry> array;
	int currentSize;
	int numHashFunctions;
	int rehashes;
	UniformRandom r;
	HashFamily hashFunctions;
public:
	explicit CuckooHashTable(int size = 101):array(size){//实际情况用素数
		numHashFunctions = hashFunctions.getNumberOfFunctions();
		rehashes = 0;
		currentSize = 0;
	};

	void makeEmpty() {
		currentSize = 0;
		for (auto& entry : array) {
			entry.isActive = false;
		}
	};

	bool contains(const AnyType& x) const {
		return findPos(x) != -1;
	};

	bool remove(const AnyType& x) {
		int currentPos = findPos(x);
		if (!isActive(currentPos)||currentPos==-1)
			return false;

		array[currentPos].isActive = false;
		--currentSize;
		return true;
	};
	bool insert(const AnyType& x) {
		if (contains(x))
			return false;

		if (currentSize >= arrat.size() * MAX_LOAD) {
			expand();
		}

		return insertHelper1(x);
	};
	bool insert(AnyType&& x) {
		if (contains(x))
			return false;

		if (currentSize >= arrat.size() * MAX_LOAD) {
			expand();
		}

		return insertHelper1(std::move(x));
	};
private:
	

	bool insertHelper1(const AnyType& xx) {
		const int COUNT_LIMIT = 100;//
		AnyType x = xx;//

		while (true) {
			int lastPos = -1;
			int pos;

			for (int count = 0; count < COUNT_LIMIT; ++count) {
				for (int i = 0; i < numHashFunctions; ++i) {
					pos = myhash(x, i);

					if (!isActive(pos)) {
						array[pos] = std::move(HashEntry(std::move(x), true));
						++currentSize;//expand()在insert()
						return true;
					}
				}
				int i = 0;
				do {
					pos = myhash(x, r.nextInt(numHashFunctions));
				} while (pos == lastPos && i++ < 5);

				lastPos = pos;
				std::swap(x, array[pos].element);
			}

			if (++rehashes > ALLOWED_REHASHES) {
				expand();
				rehashes = 0;
			}
			else {
				rehash();
			}
		}
	};
	bool insertHelper1(AnyType&& xx);
	bool isActive(int currentPos) const {
		return array[currentPos].isActive;
	};

	size_t myhash(const AnyType& x, int which) const {
		return hashFunction.hash(x, which) % array.size();
	};
	int findPos(const AnyType& x) const {
		for (int i = 0; i < numHashFunctions; ++i) {
			int pos = myhash(x, i);
			if (isActive(pos) && array[pos].element == x)
				return pos;
		}
		return - 1;
	};
	void expand() {
		rehash(static_cast<int>(array.size() / MAX_LOAD));
	};
	void rehash() {
		hashFunctions.generateNewFunctions();
		rehash(array.size());
	};
	void rehash(int newSize) {
		vector<HashEntry> oldArray = array;

		array.resize(newSize * 2 + 3);
		for (auto& entry : oldArray) {
			if (entry.isActive) {
				insert(std::move(element));
			}
		}
	};
};
template<int count>
class StringHashFamily {
private:
	vector<int> MULTIPLIERS;
	UniformRandom r;
public:
	StringHashFamily() :MULTIPLIERS(count) {
		generateNewFunctions();
	}
	int getNumberOfFunctions() {
		return count;
	}
	void generateNewFunctions() {
		for (auto& mult : MULTIPLIERS) {
			mult = r.nextInt();
		}
	}
	size_t hash(const string& x, int which) const{
		const int multiplier = MULTIPLIERS[which];
		size_t hashVal = 0;

		for (auto ch : x) {
			hashVal = multiplier * hashVal + ch;
		}
		
		return hashVal;
	}
};
#endif