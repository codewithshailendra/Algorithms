#pragma once
#include <memory>
#include <map>
#include <set>
#include <queue>
#include <functional>
#include <algorithm>
#include "Graph.h"
#include "Vertex.h"
#include "EdgeSortCriterion.h"

//API from Cormen p658
//Slow Dijkstra using a brute force search on an STL map to find cheapest vertex instead of a priority queue
class Dijkstra
{
public:
	Dijkstra(Graph & graph, int source);
	~Dijkstra();
	int shortestPath(int v);
	void shortestPaths();
	void printPath(int v);
	void printPaths();

private:
	Graph g_;
	std::map<int, Vertex> q_;
	std::map<int, Vertex> v_;
	int source_;

	void addVertex(int v);
	bool has(int v);
	bool lacks(int v);
	void relax(int u, int v);
	void initialiseSingleSource();
	void heapInsert();
	Vertex extractMin();
	void updateHeap(int v);
	void dijkstra(int u);
};