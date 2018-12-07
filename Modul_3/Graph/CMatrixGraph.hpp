#include "IGraph.h"

class CMatrixGraph : public IGraph{
public:
    CMatrixGraph(unsigned int verticesNumber);
    CMatrixGraph(const IGraph* graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

private:
    unsigned int verticesNumber_;
    std::vector<std::vector<bool>> edges_;

};