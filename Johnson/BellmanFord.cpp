#include "BellmanFord.h"

BellmanFord::BellmanFord(Graph & graph, int source) :
	g_{ graph }, v_{}, source_{ source }, negativeLoop_{ false }
{
	for (auto const & node : g_.adj_) {
		//first is source node  second is map<destination node, weight>
		addVertex(node.first);
		for (auto const & dest : node.second) {
			addVertex(dest.first);
		}
	}
	if (!g_.hasNegativeEdges()) {
		std::cout << "No negative edges found - use Dijkstra for single source shortest path\n";
	}
	if (lacks(source_)) {
		std::cout << "Source vertex " << source_ << " is not present in graph\n";
		throw std::exception("Source vertex is not present in graph\n");
	}
	initialiseSingleSource(source_);
	if (TRACE) { std::cout << "BellmanFord started\n"; }
	bellmanFord(source_);
	if (TRACE) { std::cout << "BellmanFord complete\n"; }
}

BellmanFord::~BellmanFord()
{
}

bool BellmanFord::hasNegativeLoop()
{
	return negativeLoop_;
}

int BellmanFord::shortestPath()
{
	int sp{ INT_MAX };
	for (auto const & vertex : v_) {
		if (vertex.second.d < sp) {
			sp = vertex.second.d;
		}
	}
	return sp;
}

int BellmanFord::shortestPath(int v)
{
	if (lacks(v)) { std::cout << "Destination vertex " << v << " is not present in graph\n"; }
	if (TRACE) { std::cout << "Shortest path from " << source_ << " to " << v << " is " << v_.at(v).d << std::endl; }
	return  v_.at(v).d;
}

void BellmanFord::shortestPaths()
{
	if (g_.V() > 100) { std::cout << "\nGraph to large to display\n"; return; }
	std::cout << "Bellman Ford distances from node " << source_ << "\n";
	for (auto const & destination : v_) {
		// first: node number - second: Vertex (d=shortest path pred=predecessor)
		std::cout << "  -> " << destination.first << " = " << destination.second.d << "\n";
	}
	std::cout << std::endl;
}

void BellmanFord::printPath(int v)
{
	if (lacks(v)) { std::cout << "Destination " << v << " not present\n"; return; }
	if (v == source_) {
		std::cout << source_ << ", ";
	}
	else if (v_.at(v).pred == none) {
		std::cout << "No path from " << source_ << " to " << v << " exists\n";
	}
	else {
		printPath(v_.at(v).pred);
		std::cout << v << ", ";
	}
}

void BellmanFord::printPaths()
{
	if (g_.V() > 100) { std::cout << "\nGraph to large to display\n"; return; }
	std::cout << "Bellman Ford paths from node " << source_ << "\n";
	for (auto const & destination : v_) {
		// first: node number - second: Vertex (d=shortest path pred=predecessor)
		std::cout << "  -> node " << destination.first << ": ";
		printPath(destination.first);
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void BellmanFord::addVertex(int v)
{
	if (lacks(v)) {
		v_.emplace(v, Vertex());
	}
}

bool BellmanFord::has(int v)
{
	return (v_.count(v) != 0);
}

bool BellmanFord::lacks(int v)
{
	return (v_.count(v) == 0);
}

void BellmanFord::relax(int u, int v)
{
	if (v_.at(u).d == inf) {
		return; 
	};
	int w{ g_.adj_.at(u).at(v) };
	if (TRACE) { std::cout << "weight from " << u << " to " << v << " = " << w << "\n"; }
	int testValue{ v_.at(u).d + w };
	if (v_.at(v).d > testValue) {
		v_.at(v).d = testValue;
		v_.at(v).pred = u;
	}
	if (TRACE) { std::cout << "u = " << u << " v = " << v << " v[" << v << "] : d = " << v_.at(v).d << "  pred = " << v_.at(v).pred << "\n"; }
}

bool BellmanFord::initialiseSingleSource(int s)
{
	if (lacks(s)) {
		return false;
	}
	for (auto & v : v_) {
		v.second.d = inf;
		v.second.pred = none;
	}
	v_.at(s).d = 0;
	return true;
}

void BellmanFord::checkForNegativeLoop() {
	for (auto const & u : g_.adj_) {
		//first: node number - second: adjacency map<destination, weight>
		for (auto const & v : u.second) {
			//first: destination node number - second: weight
			if (v_.at(v.first).d > v_.at(u.first).d + u.second.at(v.first)) {
				negativeLoop_ = true;
				return;
			}
		}
	}
}

void BellmanFord::bellmanFord(int u)
{
	auto loopCounter{ v_.size() - 1 };
	while (loopCounter) {
		for (auto const & node : g_.adj_.at(source_)) {
			//first: destination node number - second weight
			relax(source_, node.first);
		}
		for (auto const & node : g_.adj_) {
			//first: node number - second: adjacency map<desitination node number, weight>
			if (node.first != source_) {
				for (auto const & v : node.second) {
					//first: destination node number - second: weight of edge
					relax(node.first, v.first);
				}
			}
		}
		loopCounter--;
	}
	checkForNegativeLoop();
}




