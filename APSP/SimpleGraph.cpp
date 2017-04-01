#include "SimpleGraph.h"


SimpleGraph::SimpleGraph(std::string fname) : adj_{}, v_{ 0 }, e_{ 0 }, negativeEdges_{ false }
{
	getData(fname);
	negativeEdges();
	if (TRACE) { std::cout << "Read " << v_ << " vertices and " << e_ << " edges\n"; }
}

SimpleGraph::~SimpleGraph()
{
}

const std::shared_ptr<std::map<int, std::map<int, int>>> SimpleGraph::adj()
{
	return std::make_shared<std::map<int, std::map<int, int>>>(adj_);
}

const std::shared_ptr<std::map<int, int>> SimpleGraph::adj(int u)
{
	if (has(u)) return std::make_shared<std::map<int, int>>(adj_.at(u));
	if (TRACE) { std::cout << "WARNING: Returning an empty set of adjacencies\n"; }
	return std::make_shared<std::map<int, int>>(adj_.at(u));
}

int SimpleGraph::weight(int u, int v)
{
	if (lacks(u) || lacks(v)) { return inf; }
	auto adjacencies = adj_.at(u);
	if (adjacencies.find(v) == adjacencies.cend()) {return inf;}
	return adjacencies.at(v);
}

int SimpleGraph::V()
{
	v_ = static_cast<int>(adj_.size());
	return v_;
}

int SimpleGraph::E()
{
	return e_;
}

bool SimpleGraph::hasNegativeEdges()
{
	return negativeEdges_;
}

bool SimpleGraph::negativeEdges()
{
	negativeEdges_ = false;
	for (auto const & v : adj_) {
		for (auto const & e : v.second) {
			if (e.second < 0) { 
				negativeEdges_ = true;
				if (TRACE) { std::cout << "Negative weight of " << e.second << " found at node " << v.first << "\n"; }
				return negativeEdges_; }
		}
	}
	return negativeEdges_;
}

bool SimpleGraph::lacks(int v)
{
	return adj_.find(v) == adj_.cend();
}

bool SimpleGraph::has(int v)
{
	return adj_.find(v) != adj_.cend();
}

void SimpleGraph::addVertex(int v)
{
	if (lacks(v)) {
		adj_.emplace(v,std::map<int,int>());
	}
}

void SimpleGraph::addEdge(int u, int v, int w)
{
	addVertex(u);
	addVertex(v);
	adj_.at(u).emplace(v, w);
	e_++;
}

void SimpleGraph::getData(std::string fname)
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
	assert(fs.is_open());

	std::string line;
	std::getline(fs, line);
	std::stringstream ss{ line };
	ss >> v_ >> e_;
	int i{ 0 }; int j{ 0 }; int w{ 0 };
	while (getline(fs, line)) {
		ss.clear();
		ss.str(line);
		ss >> i >> j >> w;
		addEdge(i, j, w);
	}
}

