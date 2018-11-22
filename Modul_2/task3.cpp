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
    node = new_node; /////////// здесь точно неправлильно

}

///////////////////////////////////////////////////////////////////////////////

class Tree {
public:
    Tree();
    ~Tree();

    void add(int key);

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


///////////////////////////////////////////////////////////////////////////////
// переписать
template <typename node_t>
int depth(node_t *node) {
    if (node == NULL) return 0;

    std::stack<node_t *> s;
    std::stack<int> depths;

    int current_depth = 0;
    int max_depth = 0;

    for (;;) {
        ++current_depth;

        if (node->left != NULL) {
            if (node->right != NULL) { s.push(node->right); depths.push(current_depth); }
            node = node->left;
        } else if (node->right != NULL) {
            node = node->right;
        } else {
            if (current_depth > max_depth) max_depth = current_depth;
            if (!s.size()) break;

            node = s.top();
            s.pop();

            current_depth = depths.top();
            depths.pop();
        }
    }

    return max_depth;
}

///////////////////////////////////////////////////////////////////////////////


int main() {
    int n = 0;
    std::cin >> n;

    Treap treap;
    Tree tree;

    for (int i = 0; i < n; i++) {
        Node treap_node(key, value); /////////////!!!!!!!!!!!!!!
        Node tree_node(key);
        treap.add(treap_node);
        tree.add(tree_node);
    }

    int depth_difference = std::abs(depth(tree) - depth(treap));

    std::cout << depth_difference << std::endl;

    /// деструкторы!!!!!!!!!!!

    return 0;
}