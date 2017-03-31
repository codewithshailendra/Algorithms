#include "DepthFirstOrder.h"

DepthFirstOrder::DepthFirstOrder(DiGraph G) : marked_{}, pre_{}, post_{}, reversePost_{}
{
	for (auto const & v : G.nodes()) {
		if (!marked(v)) {
			dfs(G, v);
		}
	}
}

bool DepthFirstOrder::marked(int v)
{
	if (marked_.find(v) == marked_.cend()) {
		return false;
	}
	return marked_.at(v);
}

void DepthFirstOrder::mark(int v)
{
	marked_[v] = true;
}

void DepthFirstOrder::dfs(DiGraph G, int v)
{
	pre_.push(v);
	mark(v);
	for (auto const & w : G.adj(v)) {
		if (!marked(w)) {
			dfs(G, w);
		}
	}
	post_.push(v);
	reversePost_.push(v);
}

DepthFirstOrder::~DepthFirstOrder()
{
}

