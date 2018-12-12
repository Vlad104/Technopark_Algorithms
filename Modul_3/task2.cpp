#include <iostream>
#include <vector>
#include <queue>

class Graph {
public:
	Graph(int vertices_count);

	void AddEdge(int from, int to);
	int VerticesCount() const;
	void GetNextVertices(int vertex, std::vector<int>& vertices) const;
	
	int PathsCount(int from, int to);
private:
	struct Vertex {
		Vertex() : paths(0), depth(0) {}
		int paths;
		int depth;
	};

	std::vector<std::vector<int>> out_edges_;
	void Bfs(int from, std::vector<Vertex>& visited);
};


Graph::Graph(int vertices_count) :
	out_edges_(vertices_count)
{}


int Graph::VerticesCount() const { 
	return out_edges_.size(); 
}

void Graph::AddEdge(int from, int to) {

	// проверка наличия ребра в графе
	for (auto edge : out_edges_[from]) {
		if (edge == to) {
			return;
		}
	}
	out_edges_[to].push_back(from);
	out_edges_[from].push_back(to);
}

void Graph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
	vertices = out_edges_[vertex];
}

int Graph::PathsCount(int from, int to) {
	std::vector<Vertex> visited(VerticesCount());
	Bfs(from, visited);
	return visited[to].paths;
}

void Graph::Bfs(int from, std::vector<Vertex>& visited) {
	std::queue<int> q;
	q.push(from);
	visited[from].paths = 1;

	while(!q.empty()) {
		int current = q.front();
		q.pop();

		std::vector<int> next_vertices;
		GetNextVertices(current, next_vertices);

		for (auto vertex : next_vertices) {
			// если не была посещена, добавляем в очередь
			if (visited[vertex].paths == 0) {
				q.push(vertex);
				visited[vertex].depth = visited[current].depth + 1;
				visited[vertex].paths = visited[current].paths;
			}
			// если была посещена, и имеет такую же глубину, увеличиваем кол-во путей
			else if (visited[vertex].depth == visited[current].depth + 1) {
				visited[vertex].paths += visited[current].paths;
			}
		}
	}
}


int main() {

	int vertices_count = 0;
	int edge_count = 0;
	int in = 0;
	int out = 0;

	std::cin >> vertices_count >> edge_count;

	Graph graph(vertices_count);
	for (int i = 0; i < edge_count; i++) {
		std::cin >> in >> out;
		graph.AddEdge(in, out);
	}

	std::cin >> in >> out;
	std::cout << graph.PathsCount(in, out) << std::endl;

	return 0;
}