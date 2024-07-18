#ifndef BTREE_H
#define BTREE_H
template<class T>
class BTree {
public:
	struct Node {
		T* key;//关键字
		Node** son;//子节点数组
		Node(int M,bool mode=true) {//M叉,mode为true表示不为数据项，存在M个son，mode为false表示最下层，此时son为nullptr
			if (mode) {
				key = new T[M - 1];//M-1个关键字
				son = new Node * [M];//M个儿子
				for (int i = 0; i < M; ++i) { son[i] = nullptr; }//初始化
			}
			else {
				key = new T[M];//M个数据
				son = nullptr;//最下层没有子节点
			}
		}
		void clear() {
			delete[] key;
			delete[] son;//不删除*son
		}

	};
private:
	Node* root;
	int M;//M个分叉
	
	void clear(Node*& p) {
		if (p == nullptr) {
			return;
		}
		
		if (p->son == nullptr) {//没有子节点(最下层的数据节点)
			delete[] p->key;
			delete p;
		}
		else {//有子节点,上层节点
			for (int i = 0; i < M; ++i) {
				clear(p->son[i]);
			}
			delete[] p->key;
			delete[] p->son;
			delete p;
		}
		
		p = nullptr;
	}

	bool contains(const T& value, Node* p) {
		if (p == nullptr) {
			return false;
		}

		//数据节点
		if (p->son == nullptr) {
			for (int i = 0; i < M; ++i) {
				if (value == p->key[i]) {
					return true;
				}
			}
			return false;
		}
		//上层节点
		for (int i = 0; i < M - 1; ++i) {
			if (value < p->key[i]) {
				return contains(value, p->son[i]);
			}
			else if (p->key[i] < value) {
				;
			}
			else {//相等的情况
				return true;
			}
		}

		return contains(value, p->son[M - 1]);//最右边
	}

	bool insert(const T& value, Node*& p) {
		if (p->son == nullptr) {
			for (int i = 0; i < M; ++i) {
				//不会写QAQ
			}
		}

		return false;
	}

public:
	BTree(int M = 6) :root(new Node(M,false)),M(M){};
	~BTree() { clear(root); }
	bool insert(const T& value) { return insert(value, root); }

	bool contains(const T& value) { return contains(value, root); }
};
#endif