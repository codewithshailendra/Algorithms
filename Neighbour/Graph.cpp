#include "Graph.h"

Graph::Graph(std::string fname) : v_{ 0 }, tour_{}, visited_{}
{
	getRaw(fname);
}

void Graph::getRaw(std::string fname)
{
	std::fstream fs;
	fs.open(fname);
	if (!fs.is_open()) {
		throw std::runtime_error("Unable to open " + fname + "\n");
	}

	std::string line;
	std::getline(fs, line);
	std::stringstream ss{ line };
	int expected{ 0 };
	ss >> v_;
	xr_ = std::vector<double>(v_);
	yr_ = std::vector<double>(v_);
	visited_ = std::vector<bool>(v_, false);
	int index{ 0 }; double x{ 0 }; double y{ 0 };
	while (getline(fs, line)) {
		ss.clear();
		ss.str(line);
		ss >> index >> x >> y;
		--index;
		xr_.at(index) = x;
		yr_.at(index) = y;
	}
	if (xr_.size() != v_ || yr_.size() != v_) {
		throw std::runtime_error("Data input error in " + fname + "\n");
	}
	fs.close();
}

double Graph::dist(int source, int dest)
{
	double h{ xr_[source] - xr_[dest] };
	double v{ yr_[source] - yr_[dest] };
	return  sqrt(h*h + v*v);
}

Node Graph::neighbour(int source)
{
	visited_[source] = true;
	if (nodes_->empty()) { return Node(0, dist(source,0)); }
	while (!nodes_->empty()) {
		Node next = nodes_->top();
		nodes_->pop();
		if (!visited_[next.dest]) { return next; }
	}
	throw std::runtime_error("Visited node found in heap for node " + std::to_string(source) + "\n");
}

void Graph::buildHeap(int source) {
	nodes_.reset();
	nodes_ = std::make_unique<heap>();
	for (int i{ 0 }; i < v_; ++i) {
		if (i == source || visited_[i]) { continue; }
		Node n(i, dist(source, i));
		nodes_->push(n);
	}
}

double Graph::calculate()
{
	Node n(0, 0);
	double distance{ 0 };
	while (tour_.size() < v_) {
		buildHeap(n.dest);
		tour_.push_back(n.dest);
		distance += n.dist;
		n = neighbour(n.dest);
	}
	distance += n.dist;
	return distance;
}