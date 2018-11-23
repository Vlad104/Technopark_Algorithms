#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

///////////////////////////////////////////////////////////////////////////////

struct Node {
    int key;
    int value;
    int height;

    Node* left;
    Node* right;

    explicit Node(const int& key, const int& value = 0) :
        key(key),
        value(value),
        height(1),
        left(nullptr),
        right(nullptr) 
    {}
    ~Node();
}

///////////////////////////////////////////////////////////////////////////////

class Treap {
public:
    Treap();
    ~Treap();

    void add(int key);
    int depth(Node* node = root_, int depth = 0);

private:
    Node* root_;
    void split(Node* node, int key, Node*& left, Node*& right);
    Node* merge(Node* left, Node* right);

}

void Treap::split(Node* node, int key, Node*& left, Node*& right) {
    if (node == nullptr) {
        left = nullptr;
        right = nullptr;
    } else if (key > node->key) {
        split(node->right, key, node->right, right);
        left = node;
    } else {
        split(node->left, key, left, node->left);
        right = node;
    }
}

Node* Treap::merge(Node* left, Node* right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }

    if (left->value > right->value) {
        left->right = Merge(left->right, right);
        return left;
    } else {
        right->left = Merge(left, right->left);
        return right;
    }
}

void Treap::add(int key, int value) {

    Node* new_node = new Node(key, value);
    if (root_ == nullptr) {
        root_ = new_node;
        return;
    }

    Node* node = root_; 
    while (value > node->value) {
        if (key > node->key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    split(node, key, node->left, node->right);
    new_node->left = node->left;
    new_node-right = node->right;
    node = new_node; /////////// здесь возможно неправильно

}

int Treap::depth(Node* node = root_, int depth = 0) {
    if (node == nullptr) {
        return depth;
    }
    return std::max(depth(node->left, depth + 1), depth(node->right, depth + 1));
}

///////////////////////////////////////////////////////////////////////////////

class Tree {
public:
    Tree();
    ~Tree();

    void add(int key);
    int depth(Node* node = root_, int depth = 0);

private:    
    Node* root_;
    Node* find(Node* node, int key);
}

void Tree::add(int key) {
    Node* node = find(root_, key);

    if (node == nullptr) {
        root_ = new Node(key);
    } else if (key <= node->key) {
        node->left = new Node(key);
    } else {
        node->right = new Node(key);
    }
}

Node* Tree::find(Node* node, int key) {
    if (node == nullptr) {
        return nullptr;
    }

    if (key == node->key) {
        return node;
    } else if (key > node->key) {
        find(node->right, key);
    } else {
        find(node->left, key);
    }
}

int Tree::depth(Node* node = root_, int depth = 0) {
    if (node == nullptr) {
        return depth;
    }
    return std::max(depth(node->left, depth + 1), depth(node->right, depth + 1));
}


///////////////////////////////////////////////////////////////////////////////

int main() {
    int n = 0;
    std::cin >> n;

    Treap treap;
    Tree tree;

    for (int i = 0; i < n; i++) {
        int key = 0;
        int value = 0;
        std::cin >> key >> value;
        treap.add(key, value);
        tree.add(key);
    }

    int depth_difference = std::abs(tree.depth() - treap.depth());

    std::cout << depth_difference << std::endl;

    /// деструкторы!!!!!!!!!!!

    return 0;
}