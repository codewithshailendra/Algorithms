#include "DFSPaths.h"

DFSPaths::DFSPaths(DiGraph G, int s) : marked_{}
{
	dfs(G, s);
}

DFSPaths::DFSPaths(DiGraph G, std::vector<int> sources) : marked_{}
{
	for (auto const & s : sources) {
		if (!marked(s)) {
			dfs(G, s);
		}
	}
}

DFSPaths::DFSPaths(DiGraph G) : marked_{}
{
	for (auto const & s : G.nodes()) {
		if (!marked(s)) {
			dfs(G, s);
		}
	}
}

bool DFSPaths::marked(int v)
{
	if (marked_.find(v) == marked_.cend()) {
		return false;
	}
	return marked_.at(v);
}

void DFSPaths::mark(int v)
{
	marked_[v] = true;
}

DFSPaths::~DFSPaths()
{
}

void DFSPaths::dfs(DiGraph G, int v)
{
	mark(v);
	for (auto const & w : G.adj(v)){
		if (!marked(w)) {
			dfs(G, w);
		}
	}
}
