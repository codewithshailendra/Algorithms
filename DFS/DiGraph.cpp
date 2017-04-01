#include "DiGraph.h"
#include "DiGraph.h"


DiGraph::DiGraph(int v) : v_{ v }, e_{ 0 }, adj_{}
{
}

DiGraph::DiGraph(std::string fname) : v_{ 0 }, e_{ 0 }, adj_{}
{
	getData(fname);
}

void DiGraph::getData(std::string name) {
	std::fstream fs;
	fs.open(name);
	if (fs.is_open()) {
		std::stringstream ss;
		std::string line;
		int v{ 0 };
		int w{ 0 };
		while (std::getline(fs, line)) {
			ss.clear();
			ss.str(line);
			ss >> v >> w;
			addEdge(v, w);
		}
	}
	fs.close();
	std::cout << V() << " nodes and " << E() << " edges\n";
}

bool DiGraph::has(int v)
{
	return adj_.find(v) != adj_.cend();
}

DiGraph::~DiGraph()
{
}

void DiGraph::addVertex(int v)
{
	if (!has(v)) {
		adj_.emplace(v, std::vector<int>());
	}
}

void DiGraph::addEdge(int v, int w)
{
	addVertex(v);
	addVertex(w);
	adj_.at(v).push_back(w);
	e_++;
}

std::vector<int> DiGraph::nodes()
{
	std::vector<int> nodes;
	for (auto const & node : adj_) {
		nodes.push_back(node.first);
	}
	return nodes;
}

std::vector<int> DiGraph::adj(int v)
{
	if (!has(v)) { return std::vector<int>(); }
	return adj_.at(v);
}

DiGraph DiGraph::reverse()
{
	DiGraph r(V());
	for (auto const & v : adj_) {
		for (auto const & w : v.second) {
			r.addEdge(w, v.first);
		}
	}
	return r;
}

std::string DiGraph::toString()
{
	std::stringstream ss;
	ss << V() << " vertices and " << E() << " edges\n";
	for (auto const & vertex : adj_) {
		ss << vertex.first << " : ";
		std::copy(vertex.second.cbegin(), vertex.second.cend(), std::ostream_iterator<int>(ss, ", "));
		ss << "\n";
	}
	return ss.str();
}
