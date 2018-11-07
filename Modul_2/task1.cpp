#include <algorithm>
#include <forward_list>
#include <iostream>
#include <string>
#include <vector>

class HashTable {
public:
	explicit HashTable(int size);
	HashTable(const HashTable&) = delete;
	HashTable& operator=(const HashTable&) = delete;

	bool Has(const std::string& key) const;
	bool Add(const std::string& key);
	bool Remove(const std::string& key);

 private:
 	int alpha = 23;
	std::vector<std::string> table;
	int Hash(const std::string& key);
};


HashTable::HashTable(int size = 8) :
    table(size)
{}

int HashTable::Hash(const std::string& key) {
	int hash = 0;
	for (int i = 0; i < key.size(); i++) {
		hash = (hash * alpha + key[i]) % table.size();
	}

}

// not rewrited
bool HashTable::Has(const std::string& key) const {
  const int hash = Hash(key) % table.size();
  const auto& list = table[hash];
  return std::find(list.begin(), list.end(), key) != list.end();
}

bool HashTable::Add(const std::string& key) {
	int hash = Hash(key);
	int new_hash = hash;
	for (int i = 0; i < table.size(); i++) {
		hash = (hash + i*i) % table.size();
		// проверка не удален или не пуст тогда 
		new_hash = hash;
		if (table[hash] == key) {
			return false;
		}
		// пока не удален или не пуст
	}
	table[new_hash] = key;
	// delete = false

	// перехеширование, если надо
}


// not rewrited
bool HashTable::Remove(const std::string& key) {
  const int hash = Hash(key) % table.size();
  auto& list = table[hash];
  if (list.empty()) return false;
  if (list.front() == key) {
    list.pop_front();
    return true;
  }
  // Итерируемся по списку, проверяя следующий элемент за текущим.
  for (auto it = list.begin(); std::next(it) != list.end(); ++it) {
    if (*std::next(it) == key) {
      // Удаляем следующий за текущим.
      list.erase_after(it);
      return true;
    }
  }
  return false;
}

// not rewrited
int main() {
  HashTable strings(80);
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