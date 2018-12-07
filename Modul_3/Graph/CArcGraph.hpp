#pragma once
#include <ostream>
#include "IGraph.h"

class CArcGraph : public IGraph{
public:

    CArcGraph(unsigned int verticesNumber);
    CArcGraph(const IGraph * graph);

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
    unsigned int verticesNumber_;
    std::vector<Edge> edges_;

};