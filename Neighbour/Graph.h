#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>
#include <queue>
#include "node.h"

using heap = std::priority_queue<Node, std::vector<Node>, nodeCompare>;

class Graph
{
public:
	Graph(std::string fname);
	double calculate();
	Node neighbour(int source);


private:
	int v_;
	std::vector<int> tour_;
	std::vector<double> xr_;
	std::vector<double> yr_;
	std::vector<bool> visited_;
	std::unique_ptr<heap> nodes_;
	void getRaw(std::string fname);
	double dist(int  row, int col);
	void buildHeap(int source);

};

