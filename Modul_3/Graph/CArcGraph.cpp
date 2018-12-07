#include "CArcGraph.hpp"

ArcGraph::ArcGraph(unsigned int verticesCount):
    verticesCount_(verticesCount)
{}



ArcGraph::ArcGraph(const IGraph* graph):
    verticesCount_(graph->VerticesCount())
{
    for(int i = 0; i < verticesCount_; i++) {
        std::vector<int> vertices;
        graph->GetNextVertices(i, vertices);
        for(auto edge : vertices) {
            AddEdge(i, edge);
        }
    }
}



void ArcGraph::AddEdge(int from, int to) {
    // провека на наличие ребра в графе
    for(const auto& edge : edges_) {
        if(edge.from == from && edge.to == to) {
            return;
        }
    }

    Edge edge(from, to);
    edges_.push_back(edge);
}



int ArcGraph::VerticesCount() const {
    return verticesCount_;
}



void ArcGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    for(const auto& edge : edges_) {
        if(edge.from == vertex) {
            vertices.push_back(edge.to);
        }
    }
}



void ArcGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    for(const auto& edge : edges_) {
        if(edge.to == vertex) {
            vertices.push_back(edge.from);
        }
    }
}
