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
#include <queue>
#include <stack>
#include <functional>
// API from Sedgewick p568
class Graph
{
public:
	Graph(int v);
	Graph(std::string fname);
	void getData();
	void getReverseData();
	void getConstraints();
	void getReverseConstraints();
	void reverseDFS();
	void kccDFS();
	int V();
	int E();
	void addVertex(int v);
	void addEdge(int v, int w);
	std::string toString();
	bool stronglyConnected(int v, int w);
	int id(int v);
	int componentCount();
	std::multimap<int, int, std::greater<int>> topComponents(int top);
	void clear();
	~Graph();
	void checkContraints();
private:
	std::string fileName_;
	int v_;
	int e_;
	int root_;
	std::shared_ptr<std::map<int, std::vector<int>>> adj_;
	std::map<int, bool> marked_;
	std::map<int, int> id_;
	std::map<int, int> nodesPerComponent_;
	std::multimap<int, int,std::greater<int>> componentSizes_;
	std::queue<int> pre_;
	std::queue<int> post_;
	std::stack<int> reversePost_;
	std::shared_ptr<std::stack<int>> stk_;
	

	bool has(int v);
	void mark(int v);
	void dfsOrder3(int v);
	bool marked(int v);
	void dfsOrder2(int v);
	void dfsOrder(int v);
	void dfs(int v);
	void dfs2(int v);
	void resetData();
	void counts();
};

