#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <exception>
#include "GraphDefs.h"

class Graph
{
public:
	Graph();
	Graph(std::string fname);
	~Graph();
	int weight(int u, int v);
	int V();
	int E();
	bool hasNegativeEdges();
	std::map<int, std::map<int, int>> adj_;

private:
	int v_;
	int e_;
	bool negativeEdges_;

	bool lacks(int v);
	bool has(int v);
	void addVertex(int v);
	void addEdge(int u, int v, int w);
	void getData(std::string fname);
	bool negativeEdges();
};

