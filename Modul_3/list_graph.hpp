#pragma once
//#include <ostream>
#include "graph.hpp"

class ListGraph : public IGraph {
public:
	explicit ListGraph(int vertices_count);


	void AddEdge(int from, int to) override;
	int VerticesCount() const override {return out_edges.size();};
	void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
	void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

	void Print(std::osrteam& out);	
private:
	std::vector<std::vector<int>> out_edges_;
	std::vector<std::vector<int>> in_edges_;
}



