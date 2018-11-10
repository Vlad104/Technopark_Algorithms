#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<class T>
struct DefaultComparator {
	int operator()(const T& l, const T& r) {
		if (l == r) {
			return 0;
		} else if (l < r) {
			return -1;
		} else {
			return 1;
		}
	}
}

template <class Key, class Value, class Comp = std::functor<int>(const Key&, const Key&)>>
class AVLTree {
	struct Node {
		Key key;
		Value value;
		int height;

		Npde* left;
		Node* right;
		explicit Node(const Key& key, const Value& value) :
			key(key),
			value(value),
			height(1),
			left(nullptr),
			right(nullptr) {

			}
	}
public:
	AVLTree();
	AVLTree(const AVLTree&) = delete;
	AVLTree(AVLTree&&) = delete;
	AVLTree& operator=(const AVLTree&) = delete;
	AVLTree& operator=(AVLTree&&) = delete;
	~AVLTree();

	Value* find(const Key& key);
	void insert(const Key& key, const Value& value) {
		root = internal_insert(root, key, value);
	}
	void erase(const Key& key) {
		root = internal_erase(root, key);
	}

	size_t size() const;
	int height() const;

private:
	Node* rotate_left(Node* node);
	Node* rotate_right(Node* node);

	int height_(Node* node) const {
		if (!node) {
			return 0;
		}
		return node->height;
	}
	int bfactor(Node* node) const {
		return height_(node->right) - height_(node->left);
	}

	void fix_height(Node* node) {
		node->height = std::max(height_(node->left), height_(node->right)) + 1;
	}

	Node* balance(Node* node) {
		int bf = bfactor(node);
		if (bf == 2) {
			if (bfactor(node->right) < 0) {
				node->right = rotate_right(node->right);
			} 
			return rotate_left(node);
		}
		if (bf == -2) {
			if (bfactor(node->left) > 0) {
				node->left = rotate_left(node->left);
			} 
			return rotate_right(node);
		}
		return node;
	}

	Node* internal_insert(Node* node, const key, const Value& value) {
		if (!node) {
			return new Node(key, value);
		}
		if (comp(key, node->key) == -1) {
			node->left = internal_insert(node->left, key, value);

		} else {
			node->right = internal_insert(node->right, key, value);
		}
		return balance(node);
	}

	Node* internal_erase(Node* node, const key) {
		if (!node) {
			return nullptr;
		} 
		if (comp(key, node->key) == -1) { // key < node->key
			node->left = internal_erase(node->left, key);
		} else if (comp(key, node->key) == 1) { // key > node->key
			node->right = internal_erase(node->right, key);
		} else {  // key == node->key
			Node* left = node->left;
			Node* right = node->right;
			delete node;
			if (!right) {
				return left;
			}
			Node* min_node = find_min(node->right);
			min_node->left = left;
			min_node->right = remove_min(node);
			return balance(min_node);
		}
		return balance(node);
	}

	Node* find_min(Node* node) {
		if(!node->left) {
			return node;
		}
		return find_min(node->left);
	}

	Node* remove_min(Node* node) {
		if(!node->left) {
			return nullptr;
		}
		node->left = remove_min(node->left);
		return balance(node);
	}


	Node* root;
	Comp comp;

}

int main(int argc, char const *argv[]) {

	return 0;
}