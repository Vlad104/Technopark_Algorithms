#include <iostream>
#include <algorithm>

struct Node {
	int key;
	int height;
	int size;

	Node* left;
	Node* right;
	explicit Node(const int& key) :
		key(key),
		height(1),
		size(1),
		left(nullptr),
		right(nullptr)
	{}
	~Node() {
		delete left;
		delete right;
	}
};

class AVLTree {
public:
	AVLTree() {};
	AVLTree(const AVLTree&) = delete;
	AVLTree(AVLTree&&) = delete;
	AVLTree& operator=(const AVLTree&) = delete;
	AVLTree& operator=(AVLTree&&) = delete;
	~AVLTree() {delete root_;};

	void add(const int& key);
	void remove(const int& key);
	int kstat(int k);

private:
	Node* root_;
	Node* rotate_left(Node* node);
	Node* rotate_right(Node* node);
	Node* balance(Node* node);
	int size(Node* node) const;
	int height(Node* node) const;
	int balance_factor(Node* node) const;
	void fix_height(Node* node);
	void fix_size(Node* node);
	Node* find_min(Node* node);
	Node* internal_add(Node* node, const int& key);
	Node* internal_remove(Node* node, const int& key);
	Node* remove_min(Node* node);

};

void AVLTree::add(const int& key) {
	root_ = internal_add(root_, key);
}

Node* AVLTree::internal_add(Node* node, const int& key) {
	if (!node) {
		return new Node(key);
	}
	if (key < node->key) {
		node->left = internal_add(node->left, key);

	}
	else {
		node->right = internal_add(node->right, key);
	}
	return balance(node);
}

void AVLTree::remove(const int& key) {
	root_ = internal_remove(root_, key);
}

Node* AVLTree::internal_remove(Node* node, const int& key) {
	if (!node) {
		return nullptr;
	}
	if (key < node->key) {
		node->left = internal_remove(node->left, key);
	}
	else if (key > node->key) {
		node->right = internal_remove(node->right, key);
	}
	else {
		if (node->left == nullptr || node->right == nullptr) {
			Node* temp = (node->left != nullptr) ? node->left : node->right;
			if (temp == nullptr) {
				temp = node;
				node = nullptr;
			}
			else {
				//node = temp;
				*node = *temp;
			}
			delete temp;
		}
		else {
			Node* min_node = find_min(node->right);
			node->key = min_node->key;
			node->right = internal_remove(node->right, min_node->key);
		}

	}
	if (node == nullptr) {
		return nullptr;
	}

	return balance(node);
}



Node* AVLTree::find_min(Node* node) {
	if (node->left == nullptr) {
		return node;
	}
	return find_min(node->left);
}


Node* AVLTree::remove_min(Node* node) {  // обдумать
	if (!node->left) {
		return nullptr;
	}
	node->left = remove_min(node->left);
	return balance(node);
}

int AVLTree::size(Node* node) const {
	return node != nullptr ? node->size : 0;
}

int AVLTree::height(Node* node) const {
	return node != nullptr ? node->height : 0;
}

void AVLTree::fix_height(Node* node) {
	node->height = std::max(height(node->left), height(node->right)) + 1;
}

void AVLTree::fix_size(Node* node) {
	node->size = size(node->left) + size(node->right) + 1;
}

Node* AVLTree::balance(Node* node) {
	fix_height(node);
	fix_size(node);

	int bf = balance_factor(node);
	if (bf == 2) {
		if (balance_factor(node->right) < 0) {
			node->right = rotate_right(node->right);
		}
		return rotate_left(node);
	}
	if (bf == -2) {
		if (balance_factor(node->left) > 0) {
			node->left = rotate_left(node->left);
		}
		return rotate_right(node);
	}
	return node;
}

int AVLTree::balance_factor(Node* node) const {
	return height(node->right) - height(node->left);
}

Node* AVLTree::rotate_left(Node* node) {
	Node* right = node->right;
	node->right = right->left;
	right->left = node;
	fix_height(node);
	fix_size(node);
	fix_height(right);
	fix_size(right);
	return right;
}

Node* AVLTree::rotate_right(Node* node) {
	Node* left = node->left;
	node->left = left->right;
	left->right = node;
	fix_height(node);
	fix_size(node);
	fix_height(left);
	fix_size(left);
	return left;
}

int AVLTree::kstat(int k) {
	//Node* result = nullptr;
	int result = 0;
	int s = size(root_);
	if (k < size(root_)) {
		Node* node = root_;
		int index = size(root_->left);

		while (index != k) {
			if (k > index) {
				node = node->right;
				index += size(node->left) + 1;
			}
			else {
				node = node->left;
				index -= size(node->right) + 1;
			}
		}
		result = node->key;
	}
	else {
		return 0;
	}

	return result;
}



int main() {
	int N = 0;
	std::cin >> N;
	AVLTree tree;

	for (int i = 0; i < N; i++) {
		int A = 0;
		int k = 0;
		std::cin >> A >> k;
		if (A >= 0) {
			tree.add(A);
		}
		else {
			tree.remove(-A);
		}
		std::cout << "Stat" << std::endl;
		std::cout << tree.kstat(k) << std::endl;

	}

	return 0;
}