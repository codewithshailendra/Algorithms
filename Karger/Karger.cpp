#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <iterator>

using namespace std;
using node = size_t;
using edge = pair<node, node>;

size_t rInt(size_t upper) {
	return rand() % upper;
}

edge randomEdge(const map<size_t, vector<size_t>> & g) {
	auto graphIterator{ g.begin() };
	auto randomOffset{ rInt(g.size()) };
	while (randomOffset--) { graphIterator++; }
	auto adjacencies{ &graphIterator->second };
	return std::make_pair(graphIterator->first, adjacencies->at(rInt(adjacencies->size())));
}

edge contract(map<size_t, vector<size_t>> & graph, edge e) {
	for (auto & node : graph) {
		for (auto & adjacency : node.second) {
			if (adjacency == e.second) {
				adjacency = e.first;
			}
		}
	}
	for (const auto adjacency : graph.at(e.second)) {
		graph.at(e.first).push_back(adjacency);
	}
	vector<size_t> newAdjacencies;
	for (auto & adjacency : graph.at(e.first)) {
		if (adjacency != e.first) {
			newAdjacencies.push_back(adjacency);
		}
	}
	graph.at(e.first) = newAdjacencies;
	graph.erase(graph.find(e.second));
	return e;
}

void addSuperNode(map<node, vector<node>> & nodes, edge e) {
	////////// NOT WORKING YET /////////////////////
	vector<node> contractedNodes;
	if (nodes.find(e.second) == nodes.cend()) { // then e.second is not a supernode
		contractedNodes.push_back(e.second);
	}
	else { // e.second is a supernode so we have to add its constituents and then delete it as a supernode
		for (const auto & n : nodes.at(e.second)) {
			contractedNodes.push_back(n);
		}
		nodes.erase(nodes.find(e.second));
	}

	if (nodes.find(e.first) == nodes.cend()) { // not yet a supernode so emplace it
		nodes.emplace(e.first, contractedNodes);
	}
	else { // already a supernode so add the new contracted nodes
		for (auto & n : contractedNodes) {
			nodes.at(e.first).push_back(n);
		}
	}
}

map <size_t, vector<size_t>> Load() {
	map<size_t, vector<size_t>> graph;
	string line;
	string f1name{ R"(C:\Users\n419\Repos\Algorithms\Sorting\Karger\kargerMinCut.txt)" };
	string fname{ R"(C:\Users\n419\Repos\Algorithms\Sorting\Karger\test.txt)" };
	ifstream dataFile(f1name);
	if (dataFile.is_open()) {
		while (getline(dataFile, line)) {
			stringstream ss{ line };
			size_t node;
			ss >> node;
			vector<size_t> adjacencies;
			size_t nextVertex;
			while (ss >> nextVertex) {
				adjacencies.push_back(nextVertex);
			}
			graph[node] = adjacencies;

		}
		dataFile.close();
		cout << "File completed" << endl;
	}
	return graph;
}

int main()
{
	map<node, vector<node>> originalGraph{ Load() };
	map<node, vector<node>> minimumCutGroup;
	size_t minimumCut{ UINT16_MAX };

	size_t loopCount{ 100 };
	size_t loop{ loopCount };

	while (loop--) {

		map<node, vector<node>> graph{ originalGraph };
		map<node, vector<node>> superNodes;

		while (graph.size() > 2) {
			edge contractedEdge{ contract(graph, randomEdge(graph)) };
			addSuperNode(superNodes, contractedEdge);
		}

		auto graphIt{ graph.cbegin() };
		size_t len{ graphIt->second.size() };
		graphIt++;
		if (graphIt->second.size() != len) {
			cout << "Error on loop " << loopCount - loop << " ";
			cout << "Lengths:  " << len << " and " << graphIt->second.size() << endl;
			return -1;
		}

		if (len < minimumCut) {
			minimumCut = len;
			minimumCutGroup.clear();
			for (auto const & sn : superNodes) {
				minimumCutGroup.emplace(sn.first, sn.second);
			}
			cout << "New minimum cut found: " << len;

			cout << endl;
		}
	}

	return 0;
}

