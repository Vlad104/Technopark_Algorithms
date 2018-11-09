/*
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. 
Хранимые строки непустые и состоят из строчных латинских букв. Хеш-функция строки должна быть реализована 
с помощью вычисления значения многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми. 
Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4. 
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки 
принадлежности данной строки множеству. 
1_1. Для разрешения коллизий используйте квадратичное пробирование. 
i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

Ввод	Вывод
+ hello OK
+ bye 	OK
? bye 	OK
+ bye 	FAIL
- bye 	OK
? bye 	FAIL
? hello OK

*/


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
	void print();

 private:
 	int alpha_;
  	int nodeCount_;
  	int nodeSize_;
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


HashTable::HashTable(int size = 8) : table(size), alpha_(23), nodeCount_(0), nodeSize_(size), rehashLevel_(0.75)  {}

int HashTable::Hash(const std::string& key) {
	int hash = 0;
	for (int i = 0; i < key.size(); i++) {
		hash = (hash * alpha_ + key[i]) % table.size();
	}
  	return hash;
}

void HashTable::Rehash() {
	std::vector<Node> temp_table(table); // copy
	for (auto j : temp_table) {
		std::cout << j.key << std::endl;
	}
	table.erase(table.begin(), table.end());
	std::cout << "cleared table" << std::endl;
	table.resize(2 * table.size());
	std::cout << "resized table with size: " << table.size() << std::endl;
	for (int i = 0; i < table.size(); i++) {
		if( !temp_table[i].isEmpty() && !temp_table[i].deleted ) {
			Add(temp_table[i].key);
		}
	}
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
	std::cout << "start add" << std::endl;
  	if ( nodeCount_ >= table.size() * 0.75) {
  		std::cout << "start rehash" << std::endl;
  		Rehash();
  	}

	int hash = Hash(key);
	std::cout << "prev hash for " << key << " is " << hash << std::endl;
  	int i = 0;
	while ( !table[hash].isEmpty() || table[hash].deleted ) {
		hash = (hash + i*i) % table.size();
		std::cout << "new hash for " << key << " is " << hash << std::endl;
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

void HashTable::print() {
	for (int i = 0; i < table.size(); i++) {
		std::cout << "i = " << i << " ";
		if (table[i].deleted) {
			std::cout << "deleted ";
		}
		if (table[i].isEmpty()) {
			std::cout << "empty ";
		}
		std::cout << table[i].key << std::endl;
	}
}

// not rewrited
int main() {
  HashTable strings(3);
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
    strings.print();
  }
  return 0;
}