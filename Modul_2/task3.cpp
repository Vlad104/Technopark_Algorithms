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
};

///////////////////////////////////////////////////////////////////////////////

class Treap {
public:
    Treap() : root_(nullptr) {};
    ~Treap() {};

    void add(int key, int value);
    int depth(Node* node, int depth);
    Node* root_;

private:
    void split(Node* node, int key, Node*& left, Node*& right);
    Node* merge(Node* left, Node* right);

};

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

/*
Node* Treap::merge(Node* left, Node* right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }

    if (left->value > right->value) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}
*/

void Treap::add(int key, int value) {

    Node* new_node = new Node(key, value);
    if (root_ == nullptr) {
        root_ = new_node;
        return;
    }

    Node* node = root_;
    Node* prev = root_;
    while (node != nullptr && value < node->value) {
        prev = node;
        if (key > node->key) {
            node = node->right;
        }
        else {
            node = node->left;
        }
    }
    //split(node, key, node->left, node->right);
    split(node, key, new_node->left, new_node->right);

    if (node == root_) {
        root_ = new_node;
    }
    else {
        if (key > prev->key) {
            prev->right = new_node;
        }
        else {
            prev->left = new_node;
        }
    }

}

int Treap::depth(Node* node, int depth_len = 0) {
    if (node == nullptr) {
        return depth_len;
    }
    return std::max(depth(node->left, depth_len + 1), depth(node->right, depth_len + 1));
}

///////////////////////////////////////////////////////////////////////////////

class Tree {
public:
    Tree() : root_(nullptr) {};
    ~Tree() {};

    void add(int key);
    int depth(Node* node, int depth);
    Node* root_;

private:    
    Node* find(Node* node, int key);
};

void Tree::add(int key) {
    if (root_ == nullptr) {
        root_ = new Node(key);
        return;
    }

    Node* node = root_;
    Node* next = root_;

    while (next != nullptr) {
        node = next;
        if (key > node->key) {
            next = next->right;
        } else {
            next = next->left;
        }
    }
    if (key > node->key) {
        node->right = new Node(key);
    } else {
        node->left = new Node(key);
    }
}

/*
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
    return nullptr;
}
*/

int Tree::depth(Node* node, int depth_len = 0) {
    if (node == nullptr) {
        return depth_len;
    }
    return std::max(depth(node->left, depth_len + 1), depth(node->right, depth_len + 1));
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

    //std::cout << tree.depth(tree.root_) << " " << treap.depth(treap.root_) << std::endl;

    int depth_difference = std::abs(tree.depth(tree.root_) - treap.depth(treap.root_));
    std::cout << depth_difference << std::endl;

    /// деструкторы!!!!!!!!!!!

    //std::cout << tree.depth(tree.root_) << std::endl;

    return 0;
}