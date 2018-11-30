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

	bool Has(const std::string& key) const;
	bool Add(const std::string& key);
	bool Remove(const std::string& key);

 private:
 	int alpha_;
  	int nodeCount_;
  	double rehashLevel_;
  	struct Node {
    	Node() : key(""), deleted(false) {}
	    std::string key;
	    bool deleted;
	    bool isEmpty() const {
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
	int new_size = 2 * table.size();
	std::vector<Node> temp_table(std::move(table)); // переносим таблицу во временный вектор
	table.resize(new_size);

  	nodeCount_ = 0;
	for (int i = 0; i < temp_table.size(); i++) {
		if (!temp_table[i].isEmpty() && !temp_table[i].deleted) {
			Add(temp_table[i].key);
		}
	}
}


bool HashTable::Has(const std::string& key) const {
	int hash = Hash(key);
  	int i = 0;
  	while (i < table.size()) {
	    hash = (hash + i) % table.size();
	    if (table[hash].key == key && !table[hash].deleted) {
	      return true;
	    }
	    if ( (table[hash].isEmpty() && !table[hash].deleted) || (i >= table.size()) ) {
	      return false;
	    }
	    i++;
  	}
  	return false;
}

bool HashTable::Add(const std::string& key) {
  	if (nodeCount_ >= table.size() * rehashLevel_) {
  		Rehash();
  	}
	int next_hash = Hash(key);
  	int hash = next_hash;
  	int i = 0;
	do {
		next_hash = (next_hash + i) % table.size();
		if (!table[hash].isEmpty() || !table[hash].deleted) {			
			hash = next_hash;
		}
	    if (table[next_hash].key == key) {
	      return false;
	    }
    	i++;
	} while (!table[next_hash].isEmpty() || table[next_hash].deleted);
	table[hash].key = key;
  	table[hash].deleted = false;
	nodeCount_++;
  	return true;
}


bool HashTable::Remove(const std::string& key) {
	int hash = Hash(key);
	int i = 0;
	while (true) {
		hash = (hash + i) % table.size();
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
