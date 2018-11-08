#include <algorithm>
#include <forward_list>
#include <iostream>
#include <string>
#include <vector>

class HashTable {
public:
	explicit HashTable(int size);
  ~HashTable() {};
  HashTable(const HashTable&) = delete;
  //HashTable(HashTable&&) = delete;
  HashTable& operator=(const HashTable&) = delete;
  //HashTable& operator=(&HashTable&&) = delete;

	bool Has(const std::string& key);
	bool Add(const std::string& key);
	bool Remove(const std::string& key);

 private:
 	int alpha_;
  int nodeCount_;
  int nodeSize_;
  struct Node {
    Node() : key(""), deleted(false) {}
    std::string key;
    bool deleted;
    bool isEmpty() {
      return key == "";
    }
  };
  std::vector<Node> table;
	int Hash(const std::string& key);
};


HashTable::HashTable(int size = 8) : table(size), alpha_(23), nodeCount_(0), nodeSize_(size)  {}

int HashTable::Hash(const std::string& key) {
	int hash = 0;
	for (int i = 0; i < key.size(); i++) {
		hash = (hash * alpha_ + key[i]) % table.size();
	}
  return hash;
}

bool HashTable::Has(const std::string& key) { // обдумать
  int hash = Hash(key);
  int i = 1;
  while ( 1 ) {
    if (table[hash].key == key && !table[hash].deleted ) {
      return true;
    }
    if (table[hash].isEmpty() && !table[hash].deleted ) {
      return false;
    }
    if ( i == table.size() ) {
      return false;
    }
    hash = (hash + i*i) % table.size();
    i++;
  }
}

bool HashTable::Add(const std::string& key) { // обдумать
  // перехеширование, если надо

	int hash = Hash(key);
  int i = 0;
	while ( !table[hash].isEmpty() || table[hash].deleted ) {
		hash = (hash + i*i) % table.size();
    if (table[hash].key == key) {
      return false;
    }
    i++;
	}
	table[hash].key = key;
  table[hash].deleted = false;
	nodeCount_++;
  return true;
}


bool HashTable::Remove(const std::string& key) { // обдумать
  int hash = Hash(key);
  int i = 1;
  while ( 1 ) {
    if (table[hash].key == key && !table[hash].deleted ) {
      table[hash].key = "";
      table[hash].deleted = true;
      return true;
    }
    if (table[hash].isEmpty() && !table[hash].deleted ) {
      return false;
    }
    if ( i == table.size() ) {
      return false;
    }
    hash = (hash + i*i) % table.size();
    i++;
  }
}

// not rewrited
int main() {
  HashTable strings(8);
  char command = 0;
  std::string key;
  while (std::cin >> command >> key) {
    switch (command) {
      case '?':
        std::cout << (strings.Has(key) ? "OK" : "FAIL") << std::endl;
        break;
      case '+':
        std::cout << (strings.Add(key) ? "OK" : "FAIL") << std::endl;
        break;
      case '-':
        std::cout << (strings.Remove(key) ? "OK" : "FAIL") << std::endl;
        break;
      default:
        std::cerr << "bad input" << std::endl;
        return 0;
    }
  }
  return 0;
}