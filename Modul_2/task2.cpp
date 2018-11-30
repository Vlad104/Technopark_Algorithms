#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

class BinTree {
public:
	BinTree() {};
	BinTree(const BinTree&) = delete;
	BinTree(BinTree&&) = delete;
	BinTree& operator=(const BinTree&) = delete;
	BinTree& operator=(BinTree&&) = delete;
	~BinTree() {delete node;};

	void Add(int key);
	std::vector<int> PostOrderer();

private:
	struct Node {
		int key;
		Node* left;
		Node* right;
		explicit Node(const int& key) : key(key), left(nullptr), right(nullptr) {}
		~Node() {
			delete left;
			delete right;
		}
	};
	Node* node = nullptr;
};

void BinTree::Add(int key) {

	if (node == nullptr) {
		node = new Node(key);
		return;
	}

	Node* new_node = new Node(key);
	Node* temp_node = node;
    while (true) {
        if ( key <= temp_node->key ) {
            if (temp_node->left) {
                temp_node = temp_node->left;
            }
            else {
                temp_node->left = new_node;
                break;
            }
        }
        else {
            if (temp_node->right) {
                temp_node = temp_node->right;
            }
            else {
                temp_node->right = new_node;
                break;
            }
        }
    }
    return;

}

std::vector<int> BinTree::PostOrderer() {
	std::vector<int> result;
	std::stack<Node*> st;
	Node* prev_node = nullptr;
	st.push(node);
	while (!st.empty() && node != nullptr) {

		Node* curr_node = st.top(); 

		if (!prev_node || prev_node->left == curr_node || prev_node->right == curr_node) {
			if (curr_node->left) {
				st.push(curr_node->left);
			}
			else if (curr_node->right) {
				st.push(curr_node->right);
			} else {
				result.push_back(curr_node->key);
				st.pop();
			}
		}
		else if (curr_node->left == prev_node) {
			if (curr_node->right) {
				st.push(curr_node->right);
			}
			else {
				result.push_back(curr_node->key);
				st.pop();
			}
		}
		else if (curr_node->right == prev_node) {
				result.push_back(curr_node->key);
			st.pop();		
		}
		prev_node = curr_node;
	}
	return result;
}


int main(int argc, char const *argv[]) {

	int N = 0;
	std::cin >> N;
	BinTree tree;
	for (int i = 0; i < N; i++) {
		int element;
		std::cin >> element;
		tree.Add(element);
	}


	auto result = tree.PostOrderer();
	for (auto key : result) {
		std::cout << key << " ";
	}
	std::cout << std::endl;	

	return 0;
}


