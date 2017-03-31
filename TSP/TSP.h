#pragma once
#include <vector>
#include <set>
#include <queue>

#include "Graph.h"
#include "Node.h"

class TSP
{
public:
	TSP(Graph G, int start);
	~TSP();
	int distance();
	std::vector<int> tour();
	
private:
	Graph g_;
	std::vector<int> vertices_;
	std::queue<int> route_;
	int start_;
	double distance_;
	int vSize_;
	
	int solve(int start);
	int minimumDistance(int vStart, std::set<int> set, Node root);
	void getRoute(Node root);
	void treeWalk(Node root);
	void printD(std::vector<std::vector<int>>& m);
};

