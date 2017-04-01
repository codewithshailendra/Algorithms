#pragma once
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <iterator>

#include "Graph.h"
#include "Node.h"
#include "SetCompare.h"
#include "SetHash.h"
#include "Combinations.h"

class TSPI
{
public:

	using Memo = std::map<std::set<int>, std::map<int, int>>;

	TSPI(Graph G, int start);
	~TSPI();
	int distance();
	std::vector<int> tour();


private:
	Graph g_;
	std::set<int> vertices_;
	std::queue<int> route_;
	Memo A_;
	std::vector<std::set<int>> allSets_;
	int start_;
	int distance_;
	int vSize_;

	std::set<int> allVertices();
	void showSet(std::set<int> const & s);
	void showSetVector(std::vector<std::set<int>> const & v);
	//int getCost(std::set<int> & set, int prevVertex, std::map<int, int> & minCostDP);
	int solve(int start);
	int calcAndSolve(int start);
	void printD(std::vector<std::vector<int>>& m);
};

