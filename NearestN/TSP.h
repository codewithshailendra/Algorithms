#pragma once
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <iterator>

#include "Graph.h"
#include "Combinations.h"

class TSP
{
public:

	using Memo = std::map<std::set<int>, std::map<int, double>>;

	TSP(Graph G, int start);
	int distance();


private:
	Graph g_;
	std::set<int> vertices_;
	int start_;
	double distance_;
	int vSize_;

	double solve(int start);
};

