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
        //edge = std::vector<bool>(verticesCount_, false);
        edge.assign(verticesCount_, false);
    }
    CopyGraph(graph);
}



void MatrixGraph::AddEdge(int from, int to) {
    edges_[from][to] = true;
}



int MatrixGraph::VerticesCount() const {
    return verticesCount_;
}



void MatrixGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    vertices.clear();
    for(int i = 0; i < verticesCount_; i++) {
        if(edges_[vertex][i]) {
            vertices.push_back(i);
        }
    }
}



void MatrixGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    vertices.clear();
    for(int i = 0; i < verticesCount_; i++) {
        if(edges_[i][vertex]) {
            vertices.push_back(i);
        }
    }
}

void MatrixGraph::Print(std::ostream& out) {
    out << "out_edges: " << std::endl;
    for (int i = 0; i < edges_.size(); i++) {
        out << i << ": ";
        for (auto out_target : edges_[i]) {
            if (out_target) {
                out << out_target << " ";
            }
        }
        out << std::endl;
    }
}