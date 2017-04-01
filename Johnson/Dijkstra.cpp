#include "Dijkstra.h"


Dijkstra::Dijkstra(Graph & graph, int source) :
	g_{ graph }, v_{}, source_{ source }
{
	for (auto const & node : g_.adj_) {
		//first is source node  second is map<destination node, weight>
		addVertex(node.first);
		for (auto const & dest : node.second) {
			addVertex(dest.first);
		}
	}
	if (g_.hasNegativeEdges()) {
		throw std::runtime_error("Negative edges found - use Bellman Ford for single source shortest path\n");
	}
	if (lacks(source_)) {
		throw std::runtime_error("Source vertex is not present in graph\n");
	}
	initialiseSingleSource();
	if (TRACE) { std::cout << "Dijkstra started\n"; }
	dijkstra(source_);
	if (TRACE) { std::cout << "Dijkstra complete\n"; }
}

Dijkstra::~Dijkstra()
{
}

int Dijkstra::shortestPath(int v)
{
	if (lacks(v)) { std::cout << "Destination vertex " << v << " is not present in graph\n"; }
	if (TRACE) { std::cout << "Shortest path from " << source_ << " to " << v << " is " << v_.at(v).d << std::endl; }
	return  v_.at(v).d;
}

void Dijkstra::shortestPaths()
{
	if (g_.V() > 100) { std::cout << "\nGraph to large to display\n"; return; }
	std::cout << "Dijkstra distances from node " << source_ << "\n";
	for (auto const & destination : v_) {
		// first: node number - second: Vertex (d=shortest path pred=predecessor)
		std::cout << "  -> " << destination.first << " = " << destination.second.d << "\n";
	}
	std::cout << std::endl;
}

void Dijkstra::printPath(int v)
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

void Dijkstra::printPaths()
{
	if (g_.V() > 100) { std::cout << "\nGraph to large to display\n"; return; }
	std::cout << "Dijkstra paths from node " << source_ << "\n";
	for (auto const & destination : v_) {
		// first: node number - second: Vertex (d=shortest path pred=predecessor)
		std::cout << "  -> node " << destination.first << ": ";
		printPath(destination.first);
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Dijkstra::addVertex(int v)
{
	if (lacks(v)) {
		v_.emplace(v, Vertex(v));
	}
}

bool Dijkstra::has(int v)
{
	return (v_.count(v) != 0);
}

bool Dijkstra::lacks(int v)
{
	return (v_.count(v) == 0);
}

void Dijkstra::relax(int u, int v)
{
	int w{ g_.adj_.at(u).at(v) };
	if (TRACE) { std::cout << "weight from " << u << " to " << v << " = " << w << "\n"; }
	if (v_.at(u).d == inf) { return; }
	int testValue{ v_.at(u).d + w };
	if (v_.at(v).d > testValue) {
		v_.at(v).d = testValue;
		v_.at(v).pred = u;
		updateHeap(v);
	}
	if (TRACE) { std::cout << "u = " << u << " v = " << v << " v[" << v << "] : d = " << v_.at(v).d << "  pred = " << v_.at(v).pred << "\n"; }
}

void Dijkstra::initialiseSingleSource()
{
	for (auto & v : v_) {
		v.second.d = inf;
		v.second.pred = none;
	}
	v_.at(source_).d = 0;
}

void Dijkstra::heapInsert()
{
	for (auto const & vertex : v_) {
		//first: node number - second: vertex struct
		q_.emplace(vertex.first, vertex.second);
	}
}

Vertex Dijkstra::extractMin()
{
	int minD{ inf };
	Vertex minVertex;
	for (auto const & v : q_) {
		//first: node number - second: Vertex (int d, int pred);
		if (v.second.d < minD) {
			minVertex = v.second;
		}
	}
	if (minVertex.n != none) { q_.erase(minVertex.n); }
	if (minVertex.n == none) {
		return minVertex;
	}
	return minVertex;
}

void Dijkstra::updateHeap(int v) {
	if (q_.find(v) != q_.end()) {
		q_.at(v) = v_.at(v);
	}
	else {
		std::cout << "Missed queue entry " << v << " with queue size " << q_.size() << "\n";
	}
}

void Dijkstra::dijkstra(int u)
{
	heapInsert();
	Vertex minVertex{ q_.at(source_) };
	while (!q_.empty()) {
		minVertex = extractMin();
		for (auto const & destination : g_.adj_.at(minVertex.n)) {
			//first: destination node number - second: weight of the edge
			relax(minVertex.n, destination.first);
		}
	}

}




