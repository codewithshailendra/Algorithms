#pragma once

#include "DiGraph.h"

// API from Sedgewick p587
class KSCC
{
public:
	KSCC(DiGraph G);
	~KSCC();
	bool marked(int v);
	bool stronglyConnected(int v, int w);
	int id(int v);
	int count();
	std::map<int, int> Counts();

private:
	std::map<int, bool> marked_;
	std::map<int,int> id_;
	std::map<int, int> counts_;
	int count_;
	void mark(int v);
	void dfs(DiGraph G, int v);
};

