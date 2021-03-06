#include "Graph.hpp"
#include <ostream>
class MatrixGraph : public IGraph{
public:
    MatrixGraph(unsigned int verticesCount);
    MatrixGraph(const IGraph* graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

	void Print(std::ostream& out);
private:
    unsigned int verticesCount_;
    std::vector<std::vector<bool>> edges_;

};