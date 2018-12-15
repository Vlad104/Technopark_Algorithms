#include <iostream>
#include <vector>
#include <set>
#include <limits>

const int inf = std::numeric_limits<int>::max()/2;

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

int Dijkstra(const ListGraph& graph, int from, int to) {

	std::vector<int> min_paths(graph.VerticesCount(), inf);
	min_paths[from] = 0;

	std::set<ListGraph::Vertice> q;
	q.emplace(ListGraph::Vertice(from, 0));

	while(!q.empty()) {
		auto vertex = *q.begin();
		q.erase(q.begin());
		
		std::vector<ListGraph::Vertice> vertices;
		graph.GetNextVertices(vertex.value, vertices);
		
		for (ListGraph::Vertice v : vertices) {

			if (min_paths[v.value] > min_paths[vertex.value] + v.path) {			
				q.erase(ListGraph::Vertice(v.value, min_paths[v.value]));
				min_paths[v.value] = min_paths[vertex.value] + v.path;
				q.emplace(ListGraph::Vertice(v.value, min_paths[v.value]));
			}
		}
	}
	if (min_paths[to] == inf) {
		return -1;
	}
	return min_paths[to];
}

int main() {

	int vertices_count = 0;
	int edge_count = 0;
	int in = 0;
	int out = 0;
	int weight = 0;

	std::cin >> vertices_count >> edge_count;

	ListGraph graph(vertices_count);
	for (int i = 0; i < edge_count; i++) {
		std::cin >> in >> out >> weight;
		graph.AddEdge(in, out, weight);
	}

	std::cin >> in >> out;
	std::cout << Dijkstra(graph, in, out) << std::endl;

	return 0;
}