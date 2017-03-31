#include "Dij.h"

Dij::Dij(std::shared_ptr<SimpleGraph> graph, int source) :
	g_{ graph },
	s_{ std::make_shared<std::map<int, std::map<int, int>>>() },
	q_{ std::make_shared<std::map<int, std::map<int, int>>>() },
	v_{ std::make_shared<std::map<int, Vertex>>() },
	source_{ source }
{
	adj_ = g_->adj();
	for (auto const & node : *adj_) {
		addVertex(node.first);
		for (auto const & edge : node.second) {
			addVertex(edge.first);
		}
	}

	if (TRACE) {
		if (g_->hasNegativeEdges()) {
			std::cout << "Negative edges found - use Bellman Ford for single source shortest path\n";
			assert(false);
		}
		if (lacks(source_)) {
			std::cout << "Source vertext " << source_ << " is not present in graph\n";
			assert(false);
		}
		else {
			std::cout << "Dijkstra initialisation complete\n";
		}
	}

	dijkstra(source_);

}

Dij::~Dij()
{
}

int Dij::shortestPath(int v)
{
	if (lacks(v)) { std::cout << "Destination vertex " << v << " is not present in graph\n"; }
	if (TRACE) { std::cout << "Shortest path from " << source_ << " to " << v << " is " << v_->at(v).d << std::endl; }
	return  v_->at(v).d;
}

void Dij::printPath(int v)
{
	if (lacks(v)) { std::cout << "Destination " << v << " not present\n"; return; }
	if (v == source_) {
		std::cout << source_ << ", ";
	}
	else if (v_->at(v).pred == none) {
		std::cout << "No path from " << source_ << " to " << v << " exists\n";
	}
	else {
		printPath(v_->at(v).pred);
		std::cout << v << ", ";
	}
}

void Dij::addVertex(int v)
{
	if (lacks(v)) {
		v_->emplace(v, Vertex());
	}
}

bool Dij::has(int v)
{
	return (v_->count(v) != 0);
}

bool Dij::lacks(int v)
{
	return (v_->count(v) == 0);
}

void Dij::Relax(int u, int v)
{
	int w{ s_->at(u).at(v) };
	if (TRACE) { std::cout << "weight from " << u << " to " << v << " = " << w << "\n"; }
	int testValue{ v_->at(u).d + w };
	if (v_->at(v).d > testValue) {
		v_->at(v).d = testValue;
		v_->at(v).pred = u;
	}
	if (TRACE) { std::cout << "u = " << u << " v = " << v << " v[" << v << "] : d = " << v_->at(v).d << "  pred = " << v_->at(v).pred << "\n"; }
}

bool Dij::InitialiseSingleSource(int s)
{
	if (lacks(s)) {
		return false;
	}
	for (auto & v : *v_) {
		v.second.d = inf;
		v.second.pred = none;
	}
	v_->at(s).d = 0;
	return true;
}

void Dij::moveNode(int u)
{
	s_->emplace(u, q_->at(u));
	q_->erase(u);
}

int Dij::extractMin() {
	int minNode{ none };
	// find the routes from s_ 
	int minWeight{ INT_MAX };
	for (auto const & node : *s_) {
		if (TRACE) { std::cout << "Searching adjacencies of node " << node.first << "\n"; }
		for (auto const & adj : node.second) {
			// that lead to q_
			if (q_->find(adj.first) != q_->cend()) {
				if (adj.second < minWeight) {
					minNode = adj.first;
				}
			}
		}
	}
	return minNode;
}

bool Dij::dijkstra(int u)
{
	assert(InitialiseSingleSource(source_));
	// All vertices start in q_ and s_ is empty
	for (auto const & u : *adj_) {
		q_->emplace(u.first, u.second);
	}
	// move source node from q_ to s_
	int minNode{ u };
	while (q_->size() != 0) {
		moveNode(minNode);
		if (TRACE) { std::cout << "Min node is " << minNode << "\n"; }
		for (auto const v : s_->at(minNode)) {
			Relax(minNode, v.first);
		}
		minNode = extractMin();
	}
	return true;
}


