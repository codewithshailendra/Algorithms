#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <stack>

class Sat
{
public:
	Sat(std::string fname, bool isAdj);
	void initialise(std::shared_ptr<std::map<int, std::vector<int>>> const & a);
	bool has(int v);
	void addVertex(int v);
	void addEdge(int v, int w);

private:
	std::string fileName_;
	int v_;
	int e_;
	int root_;
	std::shared_ptr<std::map<int, std::vector<int>>> adj_;
	std::shared_ptr<std::map<int, std::vector<int>>> rAdj_;
	std::map<int, bool> marked_;
	std::stack<int> reversePost_;
	std::map<int, int> id_;

	void getConstraints();
	void getData();
	void reverseAdj();
	void mark(int v);
	bool marked(int v);
	void dfsVisit(std::shared_ptr<std::map<int, std::vector<int>>> const & a, int v);
	void dfs(std::shared_ptr<std::map<int, std::vector<int>>> const & a);
	void sccVisit(std::shared_ptr<std::map<int, std::vector<int>>> const & a, int v);
	void scc(std::shared_ptr<std::map<int, std::vector<int>>> const & a, std::stack<int> & stk);
};

