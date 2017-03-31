#include "Graph.h"

#pragma region DataLoading

// loads a space separated value file of node adjacency pairs and creates a graph
Graph::Graph(std::string path) : clock{ 0 }, ftOrder{}, rootMap{}
{
	node = std::make_shared<std::map<Serial, Node>>();
	nodeT = std::make_shared<std::map<Serial, Node>>();
	ftOrder = std::make_shared<std::vector<Serial>>();
	//std::cout << loadAdjacencyList(path) << " nodes loaded" << std::endl;
	std::cout << loadPairs(path) << " edges loaded" << std::endl;
	std::cout << nodeCount(node) << " nodes detected" << std::endl;
}

// reloads the data from the original source file
void Graph::reload()
{
	//TODO fix this
	if (!loadPairs(source)) {
		panic(std::string("Unable to reload " + source));
	}
}

Serial Graph::loadAdjacencyList(std::string path)
{
	Serial count{ 0 };
	std::string line;
	std::ifstream dataFile(path);
	if (dataFile.is_open()) {
		while (getline(dataFile, line)) {
			std::stringstream ss{ line };
			Serial thisNode;
			ss >> thisNode;
			Adjacencies adjacencies;
			Serial nextAdj;
			while (ss >> nextAdj) {
				adjacencies->push_back(nextAdj);
			}
			node->insert({ thisNode, Node(thisNode, adjacencies) });
			count++;
		}
		dataFile.close();
	}
	return count;
}

Serial Graph::loadPairs(std::string path)
{
	Serial count{ 0 };
	std::string line;
	std::ifstream dataFile(path);
	if (dataFile.is_open()) {
		while (getline(dataFile, line)) {
			std::stringstream ss{ line };
			int thisNode{ -1 };
			int adjacency{ -1 };
			if (ss >> thisNode >> adjacency) {
				if (!(thisNode > 0 && adjacency > 0)) {
					std::cout << "Error reading input: " << thisNode << " : " << adjacency << std::endl;
					continue;
				}
				// if the node is in the graph then add the adjacency to its adjacency vector
				if (node->find(thisNode) != node->cend()) {
					node->at(thisNode).adj->push_back(adjacency);
				}
				else {
					// if the node is not in the graph then create the node with a single adjacency
					node->insert({ thisNode, Node(thisNode, adjacency) });
				}
				// for directed graphs, the adjacency may not be represented if it is a sink
				// in this case we need to create it as a new node with no adjacencies
				if (node->find(adjacency) == node->cend()) {
					node->insert({ adjacency, Node(adjacency) });
				}
			}
			else { // may have input a node with no adjacencies
				if (thisNode > 0 && adjacency == -1) {
					Node newNode(thisNode);
					node->insert({ thisNode, newNode });
				}
			}
			count++;
			//std::cout << thisNode << " : " << adjacency << std::endl;
			if ((count % 100000) == 0) std::cout << count << std::endl;
		}
		dataFile.close();
	}
	return --count;
}

#pragma endregion

#pragma region utilities

// resets the data fields every node
void Graph::resetMap(NodeMap & graph) {
	auto it{ graph->begin() };
	while (it != graph->end()) {
		it->second.Clear();
		it++;
	}
}

// computes the transpose of the graph
void Graph::transpose(NodeMap from, NodeMap to) {
	to->clear();
	Serial check{ from->size() };
	for (auto it = from->begin(); it != from->end();) {
		// some nodes may be sources so need to be added explicitly if they are not adjacencies
		if (to->find(it->first) == to->end()) { to->insert({ it->first, Node(it->first) }); }
		for (Serial v : *it->second.adj) { // each node in the adjacency list
			if (to->find(v) == to->end()) { to->insert({ v, Node(v) }); }
			to->at(v).adj->push_back(it->first);
		}
		it = from->erase(it);
	}
	if (to->size() != check) {
		std::cout << "ERROR - Transpose size mismatch\n";
	}
}

Adjacencies Graph::setOrder(NodeMap const & graph, NodeOrder order) {
	auto result = std::make_shared<std::vector<Serial>>();
	if (order == Natural) {
		for (auto const & n : *graph) {
			result->push_back(n.first);
		}
		return result;
	}
	std::map<Serial, Serial> orderMap;
	for (auto const & n : *graph) {
		orderMap[n.second.post] = n.second.id;
	}
	auto it{ orderMap.crbegin() };
	while (it != orderMap.crend()) {
		result->push_back(it->second);
		it++;
	}
	return result;
}

Serial Graph::nodeCount(NodeMap graph) {
	return node->size();
}

Serial Graph::edgeCount(NodeMap graph) {
	Serial count{ 0 };
	for (auto const & n : *graph) {
		count += n.second.adj->size();
	}
	return count;
}

bool Graph::graphCheck(NodeMap const & graph) {
	bool result{ true };
	Serial noAdj{ 0 };
	Serial loops{ 0 };
	if ((graph->size() == 0) || (graph == nullptr)) return false;
	for (auto const & n : *graph) {
		if (n.second.adj->empty()) {
			noAdj++;
			//std::cout << "Node " << n.first << " has no adjacencies\n";
			result = false;
		}
		if (((n.second.adj->size() == 1) && (n.second.adj->at(0) == n.second.id))) {
			std::cout << "Node " << n.first << " is a self loop\n";
			result = false;
		}
		for (Serial const & s : *n.second.adj) {
			if (s == n.first) {
				loops++;
				std::cout << "Node " << n.first << " contains a self loop\n";
			}
			result = false;
		}
	}
	std::cout << noAdj << " nodes " << " have no adjacencies\n";
	return result;
}

void Graph::panic(std::string msg)
{
	throw std::exception(msg.c_str());
}

#pragma endregion

#pragma region display

void Graph::status(NodeMap graph)
{
	for (auto const & n : *graph) {
		std::cout << "Node " << n.second.id << ": " << std::boolalpha << n.second.done; // << "[" << n.second.distance << "]\n";
	}
	std::cout << std::endl;
}

void Graph::show(NodeMap graph)
{
	for (auto const & n : *graph) {
		std::cout << "Node " << n.second.id << "  [" << n.second.pre << "/" << n.second.post << "]" << "  Leader: " << n.second.leader << " status = " << std::boolalpha << n.second.done;
		std::cout << "  Adj: ";
		copy(n.second.adj->cbegin(), n.second.adj->cend(), std::ostream_iterator<Serial>(std::cout, " "));
		std::cout << "\n";
	}
	std::cout << std::endl;
}

void Graph::countTrees() {
	for (auto const & n : *node) {
		rootMap[n.second.leader] = rootMap[n.second.leader] + 1;
	}

	/*
	std::cout << rootMap.size() << " SCC identified\n";
	for (auto const& rm : rootMap) {
		std::cout << "Leader: " << rm.first << " size: " << rm.second << std::endl;
	}

	*/

	for (auto const & n : *node) {
		if (n.second.leader == 33596) {
			std::cout << n.second.id << "\t" << n.second.pre << "\t" << n.second.post << "\t" << n.second.adj->size() << "\tAdj: ";
			std::copy(n.second.adj->cbegin(), n.second.adj->cend(), std::ostream_iterator<Serial>(std::cout, "\t"));
			std::cout << std::endl;
		};
	}

	std::multimap<Serial, Serial> mm;
	for (auto const & rm : rootMap) {
		mm.insert({ rm.second, rm.first });
		if (rm.first == 33596) {
			std::cout << "Leader 33596 has " << rm.second << " components\n";
		}
		else if (rm.second == 314) {
			std::cout << "Leader " << rm.first << " has " << rm.second << " components\n";
		}
	}

	Serial maxReport{ 0 };
	maxReport = (mm.size() > 10) ? 10 : mm.size();
	auto it{ mm.crbegin() };
	for (Serial i{ 0 }; i < maxReport; ++i) {
		std::cout << "SCC " << it->second << " has " << it->first << " components " << std::endl;
		it++;
	}



	/*
	if (v[434821] != 1) std::cout << "SCC " << 1 << " has changed from 434821 to " << rootMap[1] << " components " << std::endl;
	if (v[968] != 498116) std::cout << "SCC " << 498116 << " has changed from 968 to " << rootMap[498116] << " components " << std::endl;
	if (v[459] != 13934) std::cout << "SCC " << 13934 << " has changed from 459 to " << rootMap[33596] << " components " << std::endl;
	if (v[314] != 33596) std::cout << "SCC " << 33596 << " has changed from 314 to " << rootMap[13934] << " components " << std::endl;
	if (v[211] != 97128) std::cout << "SCC " << 97128 << " has changed from 211 to " << rootMap[97128] << " components " << std::endl;
	if (v[205] != 18994) std::cout << "SCC " << 18994 << " has changed from 205 to " << rootMap[18994] << " components " << std::endl;
	if (v[197] != 4479) std::cout << "SCC " << 4479 << " has changed from 197 to " << rootMap[4479] << " components " << std::endl;
	if (v[177] != 224107) std::cout << "SCC " << 224107 << " has changed from 177 to " << rootMap[224107] << " components " << std::endl;
	if (v[162] != 80272) std::cout << "SCC " << 80272 << " has changed from 162 to " << rootMap[80272] << " components " << std::endl;
	if (v[161] != 52131) std::cout << "SCC " << 52131 << " has changed from 161 to " << rootMap[52131] << " components " << std::endl;


	if (v[314] = 33596) {
		std::cout << "Leader number 33596 is reporting 314 components which is wrong" << std::endl;
		std::cout << "Content of SCC 33596: [id  pre/post  number of adjencies]" << std::endl;
		for (auto const & n : *node) {
			if (n.second.leader == 33596) {
				std::cout << n.second.id << ":" << n.second.pre << "/" << n.second.post << "  " << n.second.adj->size() << std::endl;
			};
		}
	}
	*/
	/*
	Leader 1 has 434821 components
	Leader 498116 has 968 components
	Leader 13934 has 459 components
	Leader 33596 has 314 components **** Wrong ****  should be 313
	Leader 97128 has 211 components
	Leader 18994 has 205 components
	Leader 4479 has 197 components
	Leader 224107 has 177 components
	Leader 80272 has 162 components
	Leader 52131 has 161 components*/

	//Leader number 33596 is reporting 314 components which is wrong


}

#pragma endregion

void Graph::in(NodeMap & graph, Serial s) {
	graph->at(s).pre = ++clock;
	graph->at(s).leader = leader;
	graph->at(s).done = true;
	//std::cout << "Into node " << s << " at " << clock << std::endl;
}

void Graph::out(NodeMap & graph, Serial s) {
	graph->at(s).post = ++clock;
	//std::cout << "Out of node " << s << " at " << clock << std::endl;
}

void Graph::dfsVisit(NodeMap & graph, Serial u) {
	auto stk = std::make_shared<std::stack<Serial>>();
	in(graph, u);
	stk->push(u);
	while (!stk->empty()) {
		Serial current{ stk->top() }; stk->pop();
		std::shared_ptr<std::vector<Serial>> adjacencies{ graph->at(current).adj };
		auto it{ adjacencies->begin() };
		while (it != adjacencies->end()) {
			Serial v{ *it };
			if (!graph->at(v).done) {
				in(graph, v);
				stk->push(v);
			}
			it++;
		}
		if (current != u) { out(graph, current); }
	}
	out(graph, u);
	//std::cout << "Completed node " << u << " visit at " << clock << std::endl;
}

void Graph::dfs(NodeMap & graph, Adjacencies order) {
	clock = 0;
	for (auto & u : *order) {
		if (!graph->at(u).done) {
			leader = u;
			dfsVisit(graph, u);
		}
	}
}

void Graph::SCC() {
	if (graphCheck(node)) std::cout << "Node check complete\n";
	transpose(node, nodeT);
	if (graphCheck(nodeT)) std::cout << "Transpose check complete\n";
	ftOrder = setOrder(nodeT, Natural);
	dfs(nodeT, ftOrder);
	ftOrder = setOrder(nodeT, ByPost);
	transpose(nodeT, node);
	//std::cout << "Running dfs on node\n";
	dfs(node, ftOrder);
	//show(node);
	//std::cout << "Completed SCC\n";
	countTrees();
	//std::cout << "Done\n";
}