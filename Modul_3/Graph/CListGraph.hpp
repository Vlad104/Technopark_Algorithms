#pragma once
#include <ostream>
#include "Graph.hpp"

class ListGraph : public IGraph {
public:
	ListGraph(int vertices_count);
	ListGraph(const IGraph* graph);


	void AddEdge(int from, int to) override;
	int VerticesCount() const override;
	void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
	void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

	void Print(std::ostream& out);	
private:
	std::vector<std::vector<int>> in_edges_;
	std::vector<std::vector<int>> out_edges_;
	int vertices_count_;
};