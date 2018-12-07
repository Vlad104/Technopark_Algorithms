//#include <iostream>
#include "CMatrixGraph.hpp"

MatrixGraph::MatrixGraph(unsigned int verticesCount) :
    verticesCount_(verticesCount),
    edges_(verticesCount_)
{
    for(std::vector<bool>& edge : edges_) {
        edge.assign(verticesCount_, false);
    }
}



MatrixGraph::MatrixGraph(const IGraph* graph) :
    verticesCount_(graph->VerticesCount()),
    edges_(verticesCount_)
{
    for(std::vector<bool>& edge : edges_) {
        edge.assign(verticesCount_, false);
    }

    for(int i = 0; i < verticesCount_; i++) {
        std::vector<int> vertices;
        graph->GetNextVertices(i, vertices);
        for(auto edge : vertices) {
            AddEdge(i, edge);
        }
    }
}



void MatrixGraph::AddEdge(int from, int to) {
    edges_[from][to] = true;
}



int MatrixGraph::VerticesCount() const {
    return verticesCount_;
}



void MatrixGraph::GetNextVertices(int vertex, std::vector<int> & vertices) const {
    vertices.clear();
    for(int i = 0; i < verticesCount_; i++) {
        if(edges_[vertex][i]) {
            vertices.push_back(i);
        }
    }
}



void MatrixGraph::GetPrevVertices(int vertex, std::vector<int> & vertices) const {
    vertices.clear();
    for(int i = 0; i < verticesCount_; i++) {
        if(edges_[i][vertex]) {
            vertices.push_back(i);
        }
    }
}