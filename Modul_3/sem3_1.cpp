#include <iostream>
#include <vector>
#include <cassert>

class DSU {
public:
	explicit DSU(int size);	
	int find(int element) ;
	int simple_find(int element) const;
	// element 1 and element2 must be different sets
	void merge(int element1, int element2);

private:
	std::vector<int> parent; // -1 if no parent
	std::vector<int> rank;
};

DSU::DSU(int size) : 
	parent(size, -1),
	rank(size, 1)
{}

DSU::find(int element) {
	if (parent[element] != -1) {
		return element;
	}
	return parent[element] = find(parent[element]);
}

DSU::simple_find(int element) {
	while (parent[element] != -1) {
		parent[element] = element;
	}
	return element;
}

DSU::merge(int element1, int element2) {
	const int presenter1 = find(element1);
	const int presenter2 = find(element2);

	if (rank[presenter1] > rank[presenter2]) {		
		parent[presenter2] = presenter1;
	} else if (rank[presenter1] < rank[presenter2]) {
		parent[presenter1] = presenter2;
	} else {
		parent[presenter1] = presenter2;
		++rank[presenter2];
	}
}

DSU::print() const {
	for (int i =0 ; i < parent.size(), ++i) {
		std::cout << simple_find() << std::endl;
	}
}

int main() {
	DSU dsu(5);
	std::cout << dsu.find(2) << " " << dsu.find(4) << std::endl;
	dsu.merge(2, 1);
	dsu.merge(3, 4);
	dsu.merge(5, 4);
	for (int i = 0; i < 6; i++) {
		std::cout << dsu.find(i) << " ";
	}
	std::cout << std::endl;
	return 0;
}