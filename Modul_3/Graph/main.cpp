#include <iostream>
#include "CListGraph.hpp"
#include "CArcGraph.hpp"
#include "CSetGraph.hpp"
#include "CMatrixGraph.hpp"

void list_graph(const IGraph& graph_input) {
	std::cout << "ListGraph:" << std::endl;

	ListGraph graph(&graph_input);

	std::cout << "Vertices Count = " << graph.VerticesCount() << std::endl; 
	std::vector<int> prev_vertices;
	graph.GetPrevVertices(1, prev_vertices);
	std::cout << "In edges for vertex 1 = ";
	for (int prev : prev_vertices) {
		std::cout << "(" << prev << ", 1), ";
	}
	std::cout << std::endl;
	graph.Print(std::cout);
	std::cout << std::endl;
}

void arc_graph(const IGraph& graph_input) {
	std::cout << "ArcGraph:" << std::endl;

	ArcGraph graph(&graph_input);

	std::cout << "Vertices Count = " << graph.VerticesCount() << std::endl; 
	std::vector<int> prev_vertices;
	graph.GetPrevVertices(1, prev_vertices);
	std::cout << "In edges for vertex 1 = ";
	for (int prev : prev_vertices) {
		std::cout << "(" << prev << ", 1), ";
	}
	std::cout << std::endl;
	graph.Print(std::cout);
	std::cout << std::endl;
}


void set_graph(const IGraph& graph_input) {
	std::cout << "SetGraph:" << std::endl;

	SetGraph graph(&graph_input);

	std::cout << "Vertices Count = " << graph.VerticesCount() << std::endl; 
	std::vector<int> prev_vertices;
	graph.GetPrevVertices(1, prev_vertices);
	std::cout << "In edges for vertex 1 = ";
	for (int prev : prev_vertices) {
		std::cout << "(" << prev << ", 1), ";
	}
	std::cout << std::endl;
	graph.Print(std::cout);
	std::cout << std::endl;
}

void matrix_graph(const IGraph& graph_input) {
	std::cout << "MatrixGraph:" << std::endl;

	SetGraph graph(&graph_input);

	std::cout << "Vertices Count = " << graph.VerticesCount() << std::endl; 
	std::vector<int> prev_vertices;
	graph.GetPrevVertices(1, prev_vertices);
	std::cout << "In edges for vertex 1 = ";
	for (int prev : prev_vertices) {
		std::cout << "(" << prev << ", 1), ";
	}
	std::cout << std::endl;
	graph.Print(std::cout);
	std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
	ListGraph graph(4);
	graph.AddEdge(0, 1);
	graph.AddEdge(0, 2);
	graph.AddEdge(2, 3);
	graph.AddEdge(2, 0);
	graph.AddEdge(1, 3);
	graph.AddEdge(3, 1);

	list_graph(graph);
	arc_graph(graph);
	set_graph(graph);
	matrix_graph(graph);

	return 0;
}