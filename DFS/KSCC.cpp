#include "KSCC.h"
#include "DepthFirstOrder.h"
#include <stack>

KSCC::KSCC(DiGraph G) : marked_{}, id_{}, counts_{}, count_ { 0 }
{
	DepthFirstOrder order(G.reverse());
	std::cout << "Edges reversed\n";
	std::stack<int> nodes{ order.reversePost() };
	std::cout << "Node order returned\n";
	while (!nodes.empty()) {
		int s = nodes.top();
		nodes.pop();
		if (!marked(s)) {
			dfs(G, s);
			count_++;
		}
	}
	std::cout << "SCC caclulated\n";
}

KSCC::~KSCC()
{
}

bool KSCC::marked(int v)
{
	if (marked_.find(v) == marked_.cend()) {
		return false;
	}
	return marked_.at(v);
}

bool KSCC::stronglyConnected(int v, int w)
{
	if (id_.find(v) == id_.cend() || id_.find(w) == id_.cend()) { return false; }
	return id_.at(v) == id_.at(w);
}

int KSCC::id(int v)
{
	if (id_.find(v) == id_.cend()) { return 0; }
	return id_.at(v);
}

int KSCC::count()
{
	return count_;
}

std::map<int, int> KSCC::Counts()
{
	counts_.clear();
	for (int i{ 0 }; i < count_; ++i) { counts_.emplace(i, 0); }
	for (auto const & v : id_) {
		counts_.at(v.second) += 1;
	}
	return counts_;
}

void KSCC::mark(int v)
{
	marked_[v] = true;
}

void KSCC::dfs(DiGraph G, int v)
{
	mark(v);
	id_[v] = count_;

	for (auto const & w : G.adj(v)) {
		if (!marked(w)) {
			dfs(G, w);
		}
	}
}