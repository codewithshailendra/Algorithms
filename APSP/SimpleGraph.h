#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <memory>
#include <vector>
#include <cassert>
#include <algorithm>
#include "GraphDefs.h"

class SimpleGraph
{
public:
	SimpleGraph(std::string fname);
	~SimpleGraph();
	const std::shared_ptr<std::map<int, std::map<int, int>>> adj();
	const std::shared_ptr<std::map<int, int>> adj(int u);
	int weight(int u, int v);
	int V();
	int E();
	bool hasNegativeEdges();


private:
	std::map<int,std::map<int,int>> adj_;
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

