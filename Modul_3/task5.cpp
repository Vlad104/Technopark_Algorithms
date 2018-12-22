#include <iostream>
#include <vector>
#include <set>
#include <limits>

const int inf = std::numeric_limits<int>::max()/2;

////////////////////////////////////////////////////////////////////////////////////////////////////

class ListGraph  {
public:
	ListGraph(int vertices_count);
	void AddEdge(int from, int to, int weight);
	int VerticesCount() const;

   	struct Vertice {
   		Vertice(int value, int path) :
   			value(value),
   			path(path)
   		{} 
   		int value;
   		int path;
   		bool operator<(const Vertice& other) const {
   			return ((path < other.path) || (path == other.path && value < other.value));
   		}
   	};	

	void GetNextVertices(int vertex, std::vector<Vertice>& vertices) const ;
	int GetWeight(int from, int to) const; 
private:
	std::vector<std::vector<Vertice>> out_edges_;
};


ListGraph::ListGraph(int vertices_count) :
	out_edges_(vertices_count)
{}

int ListGraph::VerticesCount() const { 
	return out_edges_.size();
}

void ListGraph::AddEdge(int from, int to, int weight) {
    out_edges_[to].emplace_back(Vertice(from, weight));
    out_edges_[from].emplace_back(Vertice(to, weight));
}

void ListGraph::GetNextVertices(int vertex, std::vector<Vertice>& vertices) const {
	vertices = out_edges_[vertex];
}

void GetWeight(int from, int to) const {
	return out_edges_[from][to].weight;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

class DSU {
public:
	explicit DSU(size_t size);

	int Find(int element);
	// element1 and element2 must be in different sets
	void Merge(int element1, int element2);

	void Print() const;

private:
	int SimpleFind(int element) const;

    std::vector<int> parent;  // -1 if no parent
	std::vector<int> rank;
};

DSU::DSU(size_t size) : 
	parent(size, -1),
    rank(size, 1) 
{}

int DSU::Find(int element) {
	if (parent[element] == -1) {
		return element;
	}
	return parent[element] = Find(parent[element]);
}

int DSU::SimpleFind(int element) const {
	while (parent[element] != -1) {
		element = parent[element];
	}
	return element;
}

void DSU::Merge(int element1, int element2) {
	const int presenter1 = Find(element1);
	const int presenter2 = Find(element2);
	assert(presenter1 != presenter2);

	if (rank[presenter1] > rank[presenter2]) {
		parent[presenter2] = presenter1;
	} else if (rank[presenter1] < rank[presenter2]) {
		parent[presenter1] = presenter2;
	} else {
		parent[presenter1] = presenter2;
		++rank[presenter2];
	}
}

void DSU::Print() const {
	for (int i = 0; i < parent.size(); ++i) {
		std::cout << SimpleFind(i) << " ";
	}
	std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	int n = 0;
	int m = 0;
	std::cin >> n >> m;

	ListGraph graph(n);

	for (int i =0; i < m; i++) {
		int from = 0;
		int to = 0;
		int weight = 0;
		std::cin >> from >> to >> weight;
		graph.add(from, to, weight);
	}

	std::cout << MIN_WEIGHT << std::endl;

	return 0;
}


