#pragma once
#include "DiGraph.h"
#include <vector>
#include <queue>
#include <stack>
#include <map>

class DepthFirstOrder
{
public:
	DepthFirstOrder(DiGraph G);
	~DepthFirstOrder();
	bool marked(int v);
	const std::queue<int> pre() { return pre_; }
	const std::queue<int> post() { return post_; }
	const std::stack<int> reversePost() { return reversePost_; }
private:
	std::map<int, bool> marked_;
	std::queue<int> pre_;
	std::queue<int> post_;
	std::stack<int> reversePost_;
	void mark(int v);
	void dfs(DiGraph, int v);
};
