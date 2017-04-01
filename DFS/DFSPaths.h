#pragma once
#include "DiGraph.h"

// API from Sedgewick p536
class DFSPaths
{
public:
	DFSPaths(DiGraph G, int s);
	DFSPaths(DiGraph G, std::vector<int> sources);
	DFSPaths(DiGraph G);
	bool marked(int v);
	~DFSPaths();

private:
	std::map<int,bool> marked_;
	void dfs(DiGraph G, int v);
	void mark(int v);
};

