#pragma once
#include <memory>
#include <map>
#include "SimpleGraph.h"
#include "Vertex.h"

//API from Cormen p658
//Slow Dijkstra using a brute force search to find cheapest edge
class Dij
{
public:
	Dij(std::shared_ptr<SimpleGraph> graph, int source);
	~Dij();
	int shortestPath(int v);
	void printPath(int v);

private:
	std::shared_ptr<SimpleGraph> g_;
	std::shared_ptr<std::map<int, std::map<int, int>>> adj_;
	std::shared_ptr<std::map<int, std::map<int, int>>> s_;
	std::shared_ptr<std::map<int, std::map<int, int>>> q_;
	std::shared_ptr<std::map<int, Vertex>> v_;
	int source_;

	void addVertex(int v);
	bool has(int v);
	bool lacks(int v);
	void Relax(int u, int v);
	bool InitialiseSingleSource(int s);
	void moveNode(int u);
	int extractMin();
	bool dijkstra(int u);
};

