#include <unordered_set>
#include "Graph.hpp"
#include <ostream>

class SetGraph : public IGraph{
public:

    SetGraph(unsigned int verticesCount);
    SetGraph(const IGraph* graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;
	void Print(std::ostream& out);
private:
    unsigned int verticesCount_;
    std::vector<std::unordered_set<int>> out_;
    std::vector<std::unordered_set<int>> in_;
};