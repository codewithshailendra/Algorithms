#pragma once
#include <memory>
#include <map>
#include "SimpleGraph.h"
#include "Vertex.h"

//API from Cormen p651
class BellmanFord
{
public:
	BellmanFord(std::shared_ptr<SimpleGraph> graph, int source);
	~BellmanFord();
	bool hasNegativeLoop();
	int shortestPath(int v);
	void printPath(int v);

private:
	std::shared_ptr<SimpleGraph> g_;
	std::shared_ptr<std::map<int, std::map<int, int>>> adj_;
	std::shared_ptr<std::map<int, Vertex>> v_;
	int source_;
	bool negativeLoop_;

	void addVertex(int v);
	bool has(int v);
	bool lacks(int v);
	void Relax(int u, int v);
	bool InitialiseSingleSource(int s);
	bool SSSP(int u);
};

