#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <stack>
#include <exception>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <array>
#include <memory>
#include "Node.h"

using NodeMap = std::shared_ptr<std::map<Serial, Node>>;
enum NodeOrder {Natural, ByPost};

class Graph
{
public:
	Graph(std::string source);
	void reload();
	void SCC();

private:
	NodeMap node;
	NodeMap nodeT;
	Serial leader{ 0 };
	Adjacencies ftOrder;
	std::map <Serial, Serial> rootMap;
	std::string source;
	Serial clock;
	Serial treeNumber;
	Serial loadPairs(std::string path);
	void resetMap(NodeMap & graph);
	Serial loadAdjacencyList(std::string path);
	Serial nodeCount(NodeMap graph);
	Serial edgeCount(NodeMap graph);
	bool graphCheck(NodeMap const & graph);
	void transpose(NodeMap from, NodeMap to);
	void countTrees();
	void in(NodeMap & graph, Serial s);
	void out(NodeMap & graph, Serial s);
	void panic(std::string msg);
	void status(NodeMap graph);
	void show(NodeMap graph);
	Adjacencies setOrder(NodeMap const & graph, NodeOrder order);
	void dfs(NodeMap & graph, Adjacencies order);
	void dfsVisit(NodeMap & graph, Serial u);
};


