#include "CSetGraph.h"

CSetGraph::CSetGraph(unsigned int verticesNumber):
    verticesNumber_(verticesNumber),
    out_(verticesNumber_),
    in_(verticesNumber_)
{}



CSetGraph::CSetGraph(const IGraph* graph):
    verticesNumber_(graph->VerticesCount()),
    out_(verticesNumber_),
    in_(verticesNumber_)
{
    for(int i = 0; i < verticesNumber_; i++) {
        vector<int> vertices;
        graph->GetNextVertices(i, vertices);
        for(int edge : vertices) {
            AddEdge(i, edge);
        }
    }
}



void CSetGraph::AddEdge(int from, int to) {
    out_[from].insert(to);
    in_[to].insert(from);
}



int CSetGraph::VerticesCount() const {
    return verticesNumber_;
}



void CSetGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
    vertices.clear();
    for(int i : out_[vertex]) {
        vertices.push_back(i);
    }
}



void CSetGraph::GetPrevVertices(int vertex, vector<int>& vertices) const {
    vertices.clear();
    for(int i : in_[vertex]) {
        vertices.push_back(i);
    }
}