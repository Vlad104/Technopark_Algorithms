#include "CArcGraph.hpp"

ArcGraph::ArcGraph(unsigned int verticesCount):
    verticesCount_(verticesCount)
{}



ArcGraph::ArcGraph(const IGraph* graph):
    verticesCount_(graph->VerticesCount())
{
    CopyGraph(graph);
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

void ArcGraph::Print(std::ostream& out) {
    out << "out_edges: " << std::endl;
    int prev_from = -1;
    for (int i = 0; i < edges_.size(); i++) {
        if (edges_[i].from == prev_from) {
            continue;
        }
        out << edges_[i].from << ": ";
        for (int j = 0; j < edges_.size(); j++) {
            if (edges_[i].from == edges_[j].from) {
                out << edges_[j].to << " ";
            }
        }
        prev_from = edges_[i].from;
        out << std::endl;
    }
}