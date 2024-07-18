#pragma once
#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include <vector>
using namespace std;
template<class Comparable>
class BinaryHeap {
public:
	explicit BinaryHeap(int capacity = 100):array(capacity),currentSize(0) {};
	explicit BinaryHeap(const vector<Comparable>& items) : array(items.size() + 1), currentSize(items.size()) {
		for (int i = 0; i < items.size(); ++i) {
			array[i + 1] = items[i];
		}
		buildHeap();
	};

	bool isEmpty() { return !currentSize; };
	const Comparable& findMin() const { return array[1]; };

	void insert(const Comparable& x) {
		if (currentSize == array.size() - 1) {
			array.resize(array.size() * 2);
		}

		int hole = ++currentSize;
		array[0] = x;

		for (; x < array[hole / 2]; hole /= 2) {
			array[hole] = array[hole / 2];
		}
		array[hole] = std::move(array[0]);
	};
	void insert(Comparable&& x) {
		if (currentSize == array.size() - 1) {
			array.resize(array.size() * 2);
		}

		int hole = ++currentSize;
		array[0] = std::move(x);

		for (; x < array[hole / 2]; hole /= 2) {
			array[hole] = array[hole / 2];
		}
		array[hole] = std::move(array[0]);
	};

	void deleteMin() {
		if (isEmpty()) {
			throw;
		}

		array[1] = std::move(array[currentSize--]);
		percolateDown(1);
	};
	void deleteMin(Comparable& minItem) {
		if (isEmpty()) {
			throw;
		}

		minItem = array[1];
		array[1] = std::move(array[currentSize--]);
		percolateDown(1);
	};
	void makeEmpty() {//ÀÁ¶èÉ¾³ý
		currentSize = 0;
	};

private:
	int currentSize;
	vector < Comparable> array;

	void buildHeap() {
		for (int i = currentSize / 2; i > 0; --i) {
			percolateDown(i);
		}
	};
	void percolateDown(int hole) {
		int child;
		Comparable tmp = std::move(array[hole]);

		for (; hole * 2 <= currentSize; hole = child) {
			child = hole * 2;
			if (child != currentSize && array[child + 1] < array[child]) {
				++child;
			}
			if (array[child] < tmp) {
				array[hole] = std::move(array[child]);
			}
			else
				break;
		}

		array[hole] = std::move(tmp);
	};
};
#endif