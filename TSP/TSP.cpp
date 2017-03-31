#include "TSP.h"


TSP::TSP(Graph G, int start) : g_{ G }, vertices_{}, route_{}, start_{ start }, distance_{ 0 }, vSize_{ 0 }
{
	vSize_ = static_cast<int>(g_.d_.size());
	distance_ = solve(0);
}

TSP::~TSP()
{
}

int TSP::distance()
{
	return static_cast<int>(distance_);
}

std::vector<int> TSP::tour()
{
	std::vector<int> result;
	std::queue<int> route(route_);
	while (!route.empty()) {
		result.push_back(route.front());
		route.pop();
	}
	return result;
}

int TSP::solve(int start)
{
	std::set<int> vertices(vertices_.cbegin(), vertices_.cend());
	vertices.erase(start);
	Node root(start);
	int distance{ 0 };
	distance = minimumDistance(start, vertices, root);
	getRoute(root);
	return distance;
}

int TSP::minimumDistance(int vStart, std::set<int> vSet, Node root)
{
	if (vSet.empty()) {
		Node lastChild(start_);
		lastChild.selected = true;
		root.children.push_back(lastChild);
		return g_.d_.at(start_).at(0);
	}

	int child{ 0 };
	int selectedChild{ 0 };
	
	int minDistance{ INT_MAX };
	for (auto & v : vSet) {
		root.children.push_back(Node(v));
		int distanceToSource{ g_.d_.at(start_).at(v) };
		std::set<int> childSet(vSet);
		childSet.erase(v);
		int distanceFromSet{ minimumDistance(v,childSet,root.children.at(child)) };
		int thisDistance{distanceToSource + distanceFromSet};
		if (thisDistance < minDistance) {
			minDistance = thisDistance;
			selectedChild = child;
	}
		child++;
	}
	root.children.at(selectedChild).selected = true;
	return minDistance;
}

void TSP::getRoute(Node root)
{
	while (!route_.empty()) { route_.pop(); }
	route_.push(root.id);
	treeWalk(root);
}

// walk the tree to return the nodes selected for the route
void TSP::treeWalk(Node root)
{
	if (root.children.empty()) { return; }
	for (auto const & n : root.children) {
		if (n.selected) {
			route_.push(n.id);
			treeWalk(n);
		}
	}
}

void TSP::printD(std::vector<std::vector<int>> & m)
{
	std::cout << "\t";
	for (int j{ 0 }; j < vSize_; ++j) {
		std::cout << std::setw(5) << static_cast<int>(j);
	}
	std::cout << std::endl;

	for (int j{ 0 }; j < vSize_; ++j) {
		std::cout << std::setw(4) << static_cast<int>(j) << "\t";
		for (int i{ 0 }; i < vSize_; ++i) {
			std::cout << std::setw(4) << static_cast<int>(m[j][i]) << " ";
		}
		std::cout << std::endl;
	}
}