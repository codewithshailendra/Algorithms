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

class Graph2
{
public:
	Graph2();
	Graph2(std::string fname);
	~Graph2();
	std::vector<double> x_;
	std::vector<double> y_;
	std::vector<std::vector<double>> d_;

private:
	int v_;

	void getData(std::string fname);
	void setDistances();
	void printD();
};

