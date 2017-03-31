#pragma once
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <iterator>

#include "Graph2.h"
#include "Combinations.h"

class TSP
{
public:

	using Memo = std::map<std::set<int>, std::map<int, double>>;

	TSP(Graph2 G, int start);
	int distance();


private:
	Graph2 g_;
	std::set<int> vertices_;
	int start_;
	double distance_;
	int vSize_;

	double solve(int start);
};

