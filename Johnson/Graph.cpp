#include "Graph.h"

Graph::Graph() : adj_{}, v_{ 0 }, e_{ 0 }, negativeEdges_{ false }
{
	if (TRACE) { std::cout << "Default contstructed a Graph\n"; }
}

Graph::Graph(std::string fname) : adj_{}, v_{ 0 }, e_{ 0 }, negativeEdges_{ false }
{
	getData(fname);
	negativeEdges();
	if (TRACE) { std::cout << "Read " << v_ << " vertices and " << e_ << " edges\n"; }
}

Graph::~Graph()
{
}

int Graph::weight(int u, int v)
{
	if (lacks(u) || lacks(v)) { return inf; }
	auto adjacencies = adj_.at(u);
	if (adjacencies.find(v) == adjacencies.cend()) { return inf; }
	return adjacencies.at(v);
}

int Graph::V()
{
	v_ = static_cast<int>(adj_.size());
	return v_;
}

int Graph::E()
{
	return e_;
}

bool Graph::hasNegativeEdges()
{
	return negativeEdges_;
}

bool Graph::negativeEdges()
{
	negativeEdges_ = false;
	for (auto const & v : adj_) {
		for (auto const & e : v.second) {
			if (e.second < 0) {
				negativeEdges_ = true;
				if (TRACE) { std::cout << "Negative weight of " << e.second << " found at node " << v.first << "\n"; }
				return negativeEdges_;
			}
		}
	}
	return negativeEdges_;
}

bool Graph::lacks(int v)
{
	return adj_.find(v) == adj_.cend();
}

bool Graph::has(int v)
{
	return adj_.find(v) != adj_.cend();
}

void Graph::addVertex(int v)
{
	if (lacks(v)) {
		adj_.emplace(v, std::map<int, int>());
	}
}

void Graph::addEdge(int u, int v, int w)
{
	addVertex(u);
	addVertex(v);
	adj_.at(u).emplace(v, w);
	e_++;
}

void Graph::getData(std::string fname)
{
	/*
	The first line indicates the number of vertices and edges,
	respectively. Each subsequent line describes an edge (the first two
	numbers are its tail and head, respectively) and its length (the third
	number). NOTE: some of the edge lengths are negative. NOTE:
	These graphs may or may not have negative-cost cycles.
	*/
	std::fstream fs;
	fs.open(fname);
	if (!fs.is_open()) {
		throw std::runtime_error("Unable to open " + fname + "\n");
	}

	std::string line;
	std::getline(fs, line);
	std::stringstream ss{ line };
	int expected{ 0 };
	ss >> v_ >> expected;
	int i{ 0 }; int j{ 0 }; int w{ 0 };
	while (getline(fs, line)) {
		ss.clear();
		ss.str(line);
		ss >> i >> j >> w;
		addEdge(i, j, w);
	}
	if (e_ != expected) {
		throw std::runtime_error("Data input error in " + fname + "\n");
	}
}

