#include "CListGraph.hpp"
//#include <iostream>
#include <cassert>

ListGraph::ListGraph(int vertices_count) :
	in_edges_(vertices_count),
	out_edges_(vertices_count)
{}

ListGraph::ListGraph(const IGraph* graph) :
	in_edges_(graph->VerticesCount()),
	out_edges_(graph->VerticesCount())
{
	CopyGraph(graph);
}

int ListGraph::VerticesCount() const { 
	return out_edges_.size(); 
}

void ListGraph::AddEdge(int from, int to) {
	assert(from >= 0 && from < VerticesCount());
	assert(to >= 0 && to < VerticesCount());

	// проверка наличия ребра в графе
	for (auto edge : in_edges_[to]) {
		if (edge == from) {
			return;
		}
	}
	for (auto edge : out_edges_[from]) {
		if (edge == to) {
			return;
		}
	}

	in_edges_[to].push_back(from);
	out_edges_[from].push_back(to);
}

void ListGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
	assert(vertex >= 0 && vertex < VerticesCount());
	vertices = out_edges_[vertex];
}

void ListGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
	assert(vertex >= 0 && vertex < VerticesCount());
	vertices = in_edges_[vertex];
}

void ListGraph::Print(std::ostream& out) {
	out << "out_edges: " << std::endl;
	for (int i = 0; i < out_edges_.size(); i++) {
		out << i << ": ";
		for (auto out_target : out_edges_[i]) {
			out << out_target << " ";
		}
		out << std::endl;
	}
}