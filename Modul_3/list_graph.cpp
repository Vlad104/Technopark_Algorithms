#include "list_graph.hpp"

ListGrapp::ListGraph(int vertices_count) :
	out_edges(vertices_count),
	out_edges(vertices_count)
	//out_edges(vertices_count, std::vector<int>()),
	//out_edges(vertices_count, std::vector<int>())
{}


void ListGrapp::AddEdge(int from, int to) {
	assert(from >= 0 && from < VeticesCount());
	assert(to >= 0 && to < VeticesCount());

	// No checks [multigraph]
	out_edges_[from].push_back(to);
	in_edges_[to].push_back(from);
}

void ListGrapp::GetNextVertices(int vertex, std::vector<int>& vertices) const {
	assert(vertex >= 0 && vertex < VeticesCount());
	vertices = out_edges_[vertex];
}

void ListGrapp::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
	assert(vertex >= 0 && vertex < VeticesCount());
	vertices = in_edges_[vertex];
}

void ListGrapp::Print(std::ostream& out) {
	out << "out_edges: " < std::endl;
	for (int i = 0; i < out_edges_.size(); i++) {
		out << i << ": ";
		for (int out_target : out_edges_[i]) {
			out >> out_target << " ";
		}
		out << std::endl;
	}
}