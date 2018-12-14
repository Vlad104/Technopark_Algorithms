#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <unordered_map>
#include <limits>

const int inf = std::numeric_limits<int>::max();

class ArcGraph {
public:
    ArcGraph(int verticesCount);

    void AddEdge(int from, int to, int weight);
    int VerticesCount() const;

   	struct Vertice {
   		Vertice(int value, int path) :
   			value(value),
   			path(path)
   		{} 
   		bool operator<(const Vertice& other) const {
   			return path < other.path;
   		}
   		int value;
   		int path;
   	};
	void GetNextVertices(int vertex, std::vector<Vertice>& vertices) const;
private:
    struct Edge {
        Edge(int from, int to, int weight) :
            from(from),
            to(to),
            weight(weight)
        {};
        int from;
        int to;
        int weight;
    };
    int verticesCount_;
    std::vector<Edge> edges_;

};


ArcGraph::ArcGraph(int verticesCount):
    verticesCount_(verticesCount)
{}

void ArcGraph::AddEdge(int from, int to, int weight) {
    edges_.emplace_back(Edge(from, to, weight));
    edges_.emplace_back(Edge(to, from, weight));
}

int ArcGraph::VerticesCount() const {
    return verticesCount_;
}

void ArcGraph::GetNextVertices(int vertex, std::vector<Vertice>& vertices) const {
    for(const auto& edge : edges_) {
        if(edge.from == vertex) {
            vertices.emplace_back(Vertice(edge.to, edge.weight));
        }
    }
}

int Dijkstra(const ArcGraph& graph, int from, int to) {

	std::unordered_map<int, int> min_paths(graph.VerticesCount()); // путь до i-ой вершины
	std::unordered_map<int, bool> visited(graph.VerticesCount()); // путь до i-ой вершины

	min_paths[from] = 0;
	visited[from] = true;

	std::multiset<ArcGraph::Vertice> q;
	q.emplace(ArcGraph::Vertice(from, 0));

	while(!q.empty()) {
		auto vertex = *q.begin();
		q.erase(q.begin());
		
		if (min_paths.find(vertex.value) == min_paths.end()) {
			min_paths[vertex.value] = inf;
		}

		std::vector<ArcGraph::Vertice> vertices;
		graph.GetNextVertices(vertex.value, vertices);
		
		for (ArcGraph::Vertice v : vertices) {
			if (min_paths.find(v.value) == min_paths.end()) {
				min_paths[v.value] = inf;
				visited[from] = false;
			}

			if (min_paths[v.value] > min_paths[vertex.value] + v.path) {
				if (min_paths[v.value] != inf) {					
					q.erase(ArcGraph::Vertice(v.value, min_paths[v.value]));
				}
					min_paths[v.value] = min_paths[vertex.value] + v.path;
				if (!visited[v.value]) {
					visited[v.value] = true;
					q.emplace(ArcGraph::Vertice(v.value, min_paths[v.value]));
				}
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

	ArcGraph graph(vertices_count);
	for (int i = 0; i < edge_count; i++) {
		std::cin >> in >> out >> weight;
		graph.AddEdge(in, out, weight);
	}

	std::cin >> in >> out;
	std::cout << Dijkstra(graph, in, out) << std::endl;

	return 0;
}