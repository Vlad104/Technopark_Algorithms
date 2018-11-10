/*

Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N. 
Требуется построить бинарное дерево, заданное наивным порядком вставки. 
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, 
то узел K добавляется в правое поддерево root; иначе в левое поддерево root. 
Выведите элементы в порядке post-order (снизу вверх).
Рекурсия запрещена.

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class BinTree() {
public:
	BinTree();
	BinTree(const BinTree&) = delete;
	BinTree(BinTree&&) = delete;
	BinTree& operator=(const BinTree&) = delete;
	BinTree& operator=(BinTree&&) = delete;
	~BinTree() {delete[] node;};

	void Add(int key);
	void PostOrderer();

private:
	struct Node {
		int key;
		Npde* left;
		Node* right;
		explicit Node(const int& key) : key(key), left(nullptr), right(nullptr) {}
		~Node() {
			delete left;
			delete right;
		}
	};
	Node* node;
}

void BinTree::Add(int key) {

	BinTree* newNode = new Node(key);
	if (!node) {
		node = newNode;
		return;
	}

	Node* tempNode = node;
    while (true) {
        if ( key < tempNode->key ) {
            if (tempNode->left) {
                tempNode = tempNode->left;
            }
            else {
                tempNode->left = newNode;
                return;
            }
        }
        else {
            if (tempNode->right) {
                tempNode = tempNode->right;
            }
            else {
                tempNode->right = newNode;
                return;
            }
        }
    }

}

void BinTree::PostOrderer() {

}



int main(int argc, char const *argv[]) {

	return 0;
}


