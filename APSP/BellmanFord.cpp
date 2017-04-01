#include "BellmanFord.h"

BellmanFord::BellmanFord(std::shared_ptr<SimpleGraph> graph, int source) :
	g_{ graph }, v_{ std::make_shared<std::map<int, Vertex>>() },
	source_{ source }, negativeLoop_{ true }
{
	adj_ = g_->adj();
	for (auto const & node : *adj_) {
		addVertex(node.first);
		for (auto const & edge : node.second) {
			addVertex(edge.first);
		}
	}

	if (TRACE) {
		if (!g_->hasNegativeEdges()) {
			std::cout << "\nNo negative edges found - use Djikstra for single source shortest path\n";
		}
		if (lacks(source_)) {
			std::cout << "\nSource vertext " << source_ << " is not present in graph\n";
		}
		else {
			std::cout << "\nBellman Ford initialisation complete\n";
		}
	}
	
	negativeLoop_ = !SSSP(source_);
	
	if (TRACE) {
		if (negativeLoop_) { std::cout << "Negative weight loop found\n"; }
	}
		
}

BellmanFord::~BellmanFord()
{
}

bool BellmanFord::hasNegativeLoop()
{
	return negativeLoop_;
}

bool BellmanFord::InitialiseSingleSource(int s)
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

bool BellmanFord::SSSP(int u) {
	InitialiseSingleSource(u);
	int maxEdges{ static_cast<int>(v_->size()) - 1 };

	while (maxEdges > 0) {
		for (auto const & u : *adj_) {
			for (auto const & v : u.second) {
				Relax(u.first, v.first);
			}
		}
		maxEdges--;
	}
	for (auto const & u : *adj_) {
		for (auto const & v : u.second) {
			if (v_->at(v.first).d > v_->at(u.first).d + g_->weight(u.first, v.first)) {
				return false;
			}
		}
	}
	return true;
}

int BellmanFord::shortestPath(int v)
{
	if (lacks(v)) { std::cout << "Destination vertext " << v << " is not present in graph\n"; }
	if (negativeLoop_) {
		if (TRACE) { std::cout << "Graph contains a negative weight loop\n"; }
		return inf;
	}
	if (TRACE) { std::cout << "Shortest path from " << source_ << " to " << v << " is " << v_->at(v).d << std::endl; }
	return  v_->at(v).d;
}

void BellmanFord::printPath(int v)
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

void BellmanFord::addVertex(int v)
{
	if (lacks(v)) {
		v_->emplace(v, Vertex());
	}
}

bool BellmanFord::has(int v)
{
	return (v_->count(v) != 0);
}

bool BellmanFord::lacks(int v)
{
	return (v_->count(v) == 0);
}

void BellmanFord::Relax(int u, int v)
{
	if (TRACE) { assert(has(u) && has(v)); }
	int w{ g_->weight(u,v) };
	if (w == inf) return;
	int testValue{ v_->at(u).d + w };
	if (v_->at(v).d > testValue) {
		v_->at(v).d = testValue;
		v_->at(v).pred = u;
	}
}
