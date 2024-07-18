#include <iostream>
#include "selfList.h"
#include "E:/Dev-Cpp/myInclude/hr.h"

using namespace std;

void tSelfList() {
	hr("tSelfList");
	selfListArr<int> s1;
	cout << boolalpha << s1.empty() << endl;
	s1.insert(1);
	s1.insert(2);
	s1.find(1);
	cout << s1.top() << endl;
	hrM();
	selfList<int> s2;
	cout << boolalpha << s2.empty() << endl;
	s2.insert(1);
	s2.insert(2);
	s2.find(1);
	cout << s2.top() << endl;
}

#include "myQueue.h"
#include "cirList.h"
void tQueue() {
	hr("tQueue");
	myQueue<int> m;
	cout << boolalpha << m.empty() << endl;
	m.push(1);
	m.push(2);
	m.pop();
	cout << m.empty() << m.top() << endl;
	hrM();
	cirList<int> cl;
	cout << boolalpha << cl.empty() << endl;
	cl.push(1);
	cl.push(2);
	cl .pop();
	cout << cl.empty() << cl.top() << endl;
}

#include <stack>

struct Node {
	char data;
	Node* left;
	Node* right;
};

void tMid() {
	hr("tMid");
	stack<char> st;
	char ch;
	Node* r = nullptr;
	while (cin >> ch) {
		if (isdigit(ch)) {
			st.push(ch);
		}
		else {
			Node* L = new Node{ st.top(),nullptr,nullptr };
			st.pop();
			Node* R = new Node{ st.top(),nullptr,nullptr };
			st.pop();
		}
	}
}

#include <string>
#include "BinarySearchTree.h"
void tBST() {
	hr("tBST");
	BinarySearchTree<string> bs;
	bs.insert("root");
	string value;
	while (cin >> value) {
		bs.insert(value);
	}
	cin.clear();
	bs.printTree();
}

#include "AvlTree.h"

void tAvlTree() {
	hr("tAvlTree");
	AvlTree<string> at;
	at.insert("root");
	string value;
	while (cin >> value) {
		at.insertFast(value);
	}
	at.show();
	at.printTree();
	
	cin.clear();
	
}

#include <vector>
#include <map>
void printHighChangeables(const map<string, vector<string>>& adjacentWords, int minWords = 15) {
	for (auto& entry : adjacentWords) {
		const vector<string>& words = entry.second;
		if (words.size() >= minWords) {
			cout << entry.first << " (" << words.size() << "):";
			for (auto& str : words) {
				cout << " " << str;
			}
			cout << endl;
		}
	}
}

bool onCharOff(const string& word1, const string& word2) {
	if (word1.length() != word2.length()) {
		return false;
	}

	int diffs = 0;

	for (int i = 0; i < word1.size(); ++i) {
		if (word1[i] != word2[i]) {
			if (++diffs > 1) {
				return false;
			}
		}
	}

	return diffs == 1;
}

map<string, vector<string>> computeAdjacentWords1(const vector <string>& words) {
	map<string, vector<string>> adjWords;

	for (int i = 0; i < words.size(); ++i) {
		for (int j = i + 1; j < words.size(); ++j) {
			if (onCharOff(words[i], words[j])) {
				adjWords[words[i]].push_back(words[j]);
				adjWords[words[j]].push_back(words[i]);
			}
		}
	}

	return adjWords;
}

map<string, vector<string>> computeAdjacentWords2(const vector<string>& words) {
	map<string, vector<string>> adjWords;
	map<int, vector<string>> wordsByLenth;

	for (auto& thisWord : words) {
		wordsByLenth[thisWord.length()].push_back(thisWord);
	}

	for (auto& entry : wordsByLenth) {
		const vector<string>& groupsWords = entry.second;

		for (int i = 0; i < groupsWords.size(); ++i) {
			for (int j = i + 1; j < groupsWords.size(); ++j) {
				if (onCharOff(groupsWords[i], groupsWords[j])) {
					adjWords[groupsWords[i]].push_back(groupsWords[j]);
					adjWords[groupsWords[j]].push_back(groupsWords[i]);
				}
			}
		}
	}

	return adjWords;
}

map<string, vector<string>> computeAdjcentWords(const vector<string>& words) {
	map<string, vector<string>> adjWords;
	map<int, vector<string>> wordsByLength;

	for (auto& str : words) {
		wordsByLength[str.length()].push_back(str);
	}

	for (auto& entry : wordsByLength) {
		const vector<string>& groupsWords = entry.second;
		int groupNum = entry.first;

		for (int i = 0; i < groupNum; ++i) {
			map<string, vector<string>> repToWord;

			for (auto& str : groupsWords) {
				string rep = str;
				rep.erase(i, 1);
				repToWord[rep].push_back(str);
			}

			for (auto& entry : repToWord) {
				const vector<string>& clique = entry.second;
				if (clique.size() >= 2) {
					for (int p = 0; p < clique.size(); ++p) {
						for (int q = p + 1; q < clique.size(); ++q) {
							adjWords[clique[p]].push_back(clique[q]);
							adjWords[clique[q]].push_back(clique[p]);
						}
					}
				}
			}


		}
	}

	return adjWords;
}

#include "mySet.h"
void tMySet() {
	hr("tMySet");
	MySet<string> ms;
	string value;
	while (cin >> value) {
		ms.insert(value);
	}
	ms.show();
	cin.clear();
	//*ms.find("hello") = "world";
	ms.move("root");
	hrM();
	ms.show();
}

#include "btree.h"
#include "HashTable.h"
#include "HashTable2.h"

void tHashTable() {
	hr("tHashTable");
	HashTable2<string> ht2;
	HashTable<string> ht;
	string str;
	while (cin >> str) {
		ht2.insert(str);
		ht.insert(str);
	}
	cin.clear();
	ht2.show();
	ht.show();
}

/*#include "ListTable.h"
void tListTable() {
	hr("tListTable");
	ListTable<string> lt;
	lt.insert("hello");
	lt.insert("world");
	cout << boolalpha << lt.contains("hello") << lt.contains("somekk") << endl;
	lt.del("hello");
	cout << boolalpha << lt.contains("hello") << lt.contains("somekk") << endl;
}
*/

template<typename tree>
void showTree(tree& p) {
	if (p == nullptr) return;

	for(tree * t = p; t != nullptr; t = p->brotherNext) {
		cout << t->data;
		showTree(t->son);
	}
}

struct myNode {
	string name;
	int line;
	friend ostream& operator<<(ostream& os, myNode mn){
		os << mn.name << ' ' << mn.line;

		return os;
	}
	bool operator<(myNode mn) const{
		return name < mn.name;
	}
};

#include <fstream>

void q4p50() {
	hr("q4p50");
	AvlTree<myNode> a;
	ifstream fin("btree.h");
	string str;
	int i = 1;
	while (getline(fin, str)) {
		a.insert({str,i});
		++i;
	}
	a.show();
}

int main() {
	tSelfList();
	tQueue();
	//tMid();
	tBST();
	//tAvlTree();
	//tMySet();
	//tHashTable();
	cout << int() << endl;
	//tListTable();
	q4p50();


	return 0;
}