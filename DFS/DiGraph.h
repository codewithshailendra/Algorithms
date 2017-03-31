#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

using nodeMap = std::map<int, std::vector<int>>;
using pNodeMap = std::shared_ptr<nodeMap>;

// API from Sedgewick p568
class DiGraph
{
public:
	DiGraph(int v);
	DiGraph(std::string fname);
	~DiGraph();

	int V() { return static_cast<int>(adj_.size()); }
	int E() { return e_; }
	void addVertex(int v);
	void addEdge(int v, int w);
	std::vector<int> nodes();
	std::vector<int> adj(int v);
	DiGraph reverse();
	std::string toString();

private:
	int v_;
	int e_;
	std::map<int, std::vector<int>> adj_;
	void getData(std::string name);
	bool has(int v);

};

