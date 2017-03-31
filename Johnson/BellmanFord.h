#pragma once
#include <memory>
#include <map>
#include <set>
#include <queue>
#include <functional>
#include "Graph.h"
#include "Vertex.h"
#include "EdgeSortCriterion.h"

//API from Cormen p651
//Bellman Ford with STL map
class BellmanFord
{
public:
	BellmanFord(Graph & graph, int source);
	~BellmanFord();
	bool hasNegativeLoop();
	int shortestPath();
	int shortestPath(int v);
	void shortestPaths();
	void printPath(int v);
	void printPaths();

private:
	Graph g_;
	std::map<int, Vertex> v_;
	int source_;
	bool negativeLoop_;

	void addVertex(int v);
	bool has(int v);
	bool lacks(int v);
	void relax(int u, int v);
	bool initialiseSingleSource(int s);
	void checkForNegativeLoop();
	void bellmanFord(int u);
};