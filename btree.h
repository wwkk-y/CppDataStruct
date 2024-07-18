#ifndef BTREE_H
#define BTREE_H
template<class T>
class BTree {
public:
	struct Node {
		T* key;//�ؼ���
		Node** son;//�ӽڵ�����
		Node(int M,bool mode=true) {//M��,modeΪtrue��ʾ��Ϊ���������M��son��modeΪfalse��ʾ���²㣬��ʱsonΪnullptr
			if (mode) {
				key = new T[M - 1];//M-1���ؼ���
				son = new Node * [M];//M������
				for (int i = 0; i < M; ++i) { son[i] = nullptr; }//��ʼ��
			}
			else {
				key = new T[M];//M������
				son = nullptr;//���²�û���ӽڵ�
			}
		}
		void clear() {
			delete[] key;
			delete[] son;//��ɾ��*son
		}

	};
private:
	Node* root;
	int M;//M���ֲ�
	
	void clear(Node*& p) {
		if (p == nullptr) {
			return;
		}
		
		if (p->son == nullptr) {//û���ӽڵ�(���²�����ݽڵ�)
			delete[] p->key;
			delete p;
		}
		else {//���ӽڵ�,�ϲ�ڵ�
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

		//���ݽڵ�
		if (p->son == nullptr) {
			for (int i = 0; i < M; ++i) {
				if (value == p->key[i]) {
					return true;
				}
			}
			return false;
		}
		//�ϲ�ڵ�
		for (int i = 0; i < M - 1; ++i) {
			if (value < p->key[i]) {
				return contains(value, p->son[i]);
			}
			else if (p->key[i] < value) {
				;
			}
			else {//��ȵ����
				return true;
			}
		}

		return contains(value, p->son[M - 1]);//���ұ�
	}

	bool insert(const T& value, Node*& p) {
		if (p->son == nullptr) {
			for (int i = 0; i < M; ++i) {
				//����дQAQ
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