#pragma once
#include <ostream>
#include "Graph.hpp"

class ArcGraph : public IGraph{
public:

    ArcGraph(unsigned int verticesCount);
    ArcGraph(const IGraph* graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;
private:

    struct Edge{
        Edge(int from, int to) :
            from(from),
            to(to)
        {};
        int from;
        int to;
    };
    unsigned int verticesCount_;
    std::vector<Edge> edges_;

};