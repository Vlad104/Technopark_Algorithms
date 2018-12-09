#include "CSetGraph.hpp"

SetGraph::SetGraph(unsigned int verticesCount):
    verticesCount_(verticesCount),
    out_(verticesCount_),
    in_(verticesCount_)
{}



SetGraph::SetGraph(const IGraph* graph):
    verticesCount_(graph->VerticesCount()),
    out_(verticesCount_),
    in_(verticesCount_)
{
    CopyGraph(graph);
}



void SetGraph::AddEdge(int from, int to) {
    out_[from].insert(to);
    in_[to].insert(from);
}



int SetGraph::VerticesCount() const {
    return verticesCount_;
}



void SetGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    vertices.clear();
    for(auto i : out_[vertex]) {
        vertices.push_back(i);
    }
}



void SetGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    vertices.clear();
    for(auto i : in_[vertex]) {
        vertices.push_back(i);
    }
}


void SetGraph::Print(std::ostream& out) {
    out << "out_edges: " << std::endl;
    for (int i = 0; i < out_.size(); i++) {
        out << i << ": ";
        for (int out_target : out_[i]) {
            out << out_target << " ";
        }
        out << std::endl;
    }
}