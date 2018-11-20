#include <iostream>
#include <string>
#include <vector>

class HashTable {
public:
	explicit HashTable(int size);
	  ~HashTable() {};
	  HashTable(const HashTable&) = delete;
	  HashTable(HashTable&&) = delete;
	  HashTable& operator=(const HashTable&) = delete;
	  HashTable& operator=(HashTable&&) = delete;

	bool Has(const std::string& key);
	bool Add(const std::string& key);
	bool Remove(const std::string& key);

 private:
 	int alpha_;
  	int nodeCount_;
  	int rehashLevel_;
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
	void Rehash();
};


HashTable::HashTable(int size = 8) : table(size), alpha_(23), nodeCount_(0), rehashLevel_(0.75)  {}

int HashTable::Hash(const std::string& key) {
	int hash = 0;
	for (int i = 0; i < key.size(); i++) {
		hash = (hash * alpha_ + key[i]) % table.size();
	}
  	return hash;
}

void HashTable::Rehash() {
	std::vector<Node> temp_table(table); // копируем таблицу во временный вектор
	table.resize(2 * table.size());
	for (int i = 0; i < table.size(); i++) { // обнуляем таблицу
    	Node node;
    	table[i] = node;
  	}
  	nodeCount_ = 0;
	for (int i = 0; i < temp_table.size(); i++) {
		if( !temp_table[i].isEmpty() && !temp_table[i].deleted ) {
			Add(temp_table[i].key);
		}
	}
}


bool HashTable::Has(const std::string& key) {
	int hash = Hash(key);
  	int i = 0;
  	while (true) {
	    hash = (hash + i*i) % table.size();
	    if (table[hash].key == key && !table[hash].deleted) {
	      return true;
	    }
	    if ( (table[hash].isEmpty() && !table[hash].deleted) || (i >= table.size()) ) {
	      return false;
	    }
	    i++;
  	}
}

bool HashTable::Add(const std::string& key) {
  	if ( nodeCount_ >= table.size() * 0.75) {
  		Rehash();
  	}

	int hash = Hash(key);
  	int i = 0;
	while (!table[hash].isEmpty() || table[hash].deleted) {
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


bool HashTable::Remove(const std::string& key) {
	int hash = Hash(key);
	int i = 0;
	while (true) {
		hash = (hash + i*i) % table.size();
		if (table[hash].key == key && !table[hash].deleted) {
			table[hash].key = "";
			table[hash].deleted = true;
			return true;
		}
		if ( (table[hash].isEmpty() && !table[hash].deleted) || (i >= table.size()) ) {
			return false;
		}
		i++;
	}
}

int main() {
	HashTable table(8);
	char command = 0;
	std::string key;
	while (std::cin >> command >> key) {
	switch (command) {
	  case '?':
	    std::cout << (table.Has(key) ? "OK" : "FAIL") << std::endl;
	    break;
	  case '+':
	    std::cout << (table.Add(key) ? "OK" : "FAIL") << std::endl;
	    break;
	  case '-':
	    std::cout << (table.Remove(key) ? "OK" : "FAIL") << std::endl;
	    break;
	  default:
	    std::cout << "FAIL" << std::endl;
	    return 0;
	}
	}
	return 0;
}
