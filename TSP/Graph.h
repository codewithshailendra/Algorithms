#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <exception>
#include <functional>

#include "GraphDefs.h"

class Graph
{
public:
	Graph();
	Graph(std::string fname);
	~Graph();
	std::vector<double> x_;
	std::vector<double> y_;
	std::vector<std::vector<int>> d_;

private:
	int v_;

	void getData(std::string fname);
	void setDistances();
	void printD();
};

