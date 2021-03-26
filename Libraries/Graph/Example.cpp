#include <iostream>
#include "Graph.h"

int main()
{
	lib::Graph<int/*, std::string*/> graph;
	graph.AddNode("First", 1);
	graph.AddNode("Second", 2, { "First" });
	graph.Dump();

	std::cout << "\n\nNEXT\n\n";

	graph.AddNode("Third", 3);
	graph.AddNeigh("Third", "Second");
	graph.AddNextNeigh("Third", "First");
	graph.Dump();

	std::cout << "\n\nNEXT\n\n";
	
	// auto == std::vector<std::pair<std::string, int>>
	auto output = graph.BFS("First", [](lib::Node<int>* node) { node->SetData(node->GetData() + 1); });
	for (const auto& elem : output) {
		std::cout << elem.first << "\t" << elem.second << "\n";
	}
	// -1 means you can't go from "first" to other nodes
	graph.Dump();

	std::cout << "\n\nNEXT\n\n";

	graph.EraseEdge("First", "Third");
	graph.Dump();
	graph.EraseNode("Third");
	graph.Dump();

	std::cout << "\n\nEND\n";
}