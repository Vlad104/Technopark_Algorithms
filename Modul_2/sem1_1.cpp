#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class HashTable {
public:
	explicit HashTable(suze_t size);
	~HashTable();
	HashTable(const HashTable&) = delete;
	HashTable(HashTable&&) = delete;
	HashTable& operator=(const HashTable&) = delete;
	HashTable& operator=(&HashTable&&) = delete;

	bool Has(const std::string& key);
	bool Add(const syd::string& key);
	bool Remove(const std::string& key);

private:
	std::vector<std::list<std::string>> table;
}
HashTable::HashTable(size_t size) : 
	table(size)
{}

bool HashTable::Add(const std::string& key) {
	const size_t hash = Hash(key) % table.size();
	const aotu& list = table[hash];
	return std::find(list.begin(), list.end(), key) != list.end();
}

bool HashTable::Has(const std::string& key) {
	const size_t hash = Hash(key) % table.size();
	const aotu& list = table[hash];
	if ( std::find(list.begin(), list.end(), key) != list.end() ) {
		return false;
	}
	list.emplace_front(key);
}

bool HashTable::Remove(const std::string& key) {
	// при удалении пробировать <= m раз во всех функциях Add, Has, Remove
	// при добавлении Add (и Has) не останавливаться на deleted, тк key может быт после него
	const size_t hash = Hash(key) % table.size();
	const auto& list = table[hash];
	if (list.empty()) {
		return false;
	}
	if (list.front() == key) {
		list.pop_front();
	}
	//auto it = std::find(list.begin(), list.end(), key);
	for (auto it = list.begin(); std::next(it) != list.end(); ++it) {
		if (*std::next(it) == key) {
			list.erase_after(it);
		}
	}
}

int Hash(const std::string) {
	if (key.empty()) {
		return 3;
	}
	return key[0];
}

int main(int argc, char const *argv[]) {
	HashTable set(8);

	while (std::cin >> command >> key) {
		switch(command) {
			case '?':
				std::cout << (string.Has(key) ? "OK" : "FAIL");
				break;
			case '+':
				std::cout << (string.Add(key) ? "OK" : "FAIL");
				break;
			case '-':
				std::cout << (string.Remove(key) ? "OK" : "FAIL");
				break;				
			default:
				std::cerr << "bad input" << std::endl;
				break;
		}
	}
	return 0;
}