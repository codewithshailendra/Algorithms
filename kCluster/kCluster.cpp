#include <iterator>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <set>
#include <map>

using namespace std;

/*
Input file describes a distance function (equivalently, a complete graph with edge costs). It has the following format:
[number_of_nodes]
[edge 1 node 1] [edge 1 node 2] [edge 1 cost]
[edge 2 node 1] [edge 2 node 2] [edge 2 cost]
...
There is one edge (i,j) for each choice of 1 <= i < j <= n, where n is the number of nodes. For example, the third line of the file is "1 3 5250",
indicating that the distance between nodes 1 and 3 (equivalently, the cost of the edge (1,3)) is 5250.
You can assume that distances are positive, but you should NOT assume that they are distinct.
Your task in this problem is to run the clustering algorithm from lecture on this data set, where the target number of clusters is set to 4.
What is the maximum spacing of a 4-clustering?

124750 edges

*/

#include <vector>
#include <memory>
#include <iostream>
#include <bitset>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <iterator>

using namespace std;
using bits = std::bitset<24>;

std::ostream & operator<<(std::ostream & os, std::vector<bits> b) {
	copy(b.cbegin(), b.cend(), std::ostream_iterator<bits>(std::cout, "\n"));
	return os;
}

class bitSort {
public:
	bool operator()(std::bitset<24> const & lhs, std::bitset<24> const & rhs) const {
		return lhs.to_ullong() < rhs.to_ullong();
	}
};

class UF {
public:
	UF() : graph_{} {};

	void insert(bits b) {
		graph_.emplace(b, b);
	}

	bits find(bits u) {
		if (graph_[u] == u) return u;
		u = graph_[u];
		return find(u);
	}

	bool join(bits u, bits v) {
		bits uRoot{ find(u) };
		bits vRoot{ find(v) };
		if (uRoot == vRoot) { return false; }
		graph_[vRoot] = uRoot;
		return true;
	}

	void clusterBy2() {
		for (auto const & node : graph_) {
			vector<bits> nearestBy2{ neighbours(node.first) };
			//cout << nearestBy2 << endl;
			// nearestBy2 contains all of the possible neigbours of the current node 
			for (auto const & candidate : nearestBy2) {
				// if the candidate neighbour is not in the graph then there is nothing to do 
				if (graph_.find(candidate) != graph_.cend()) {
					// otherwise put the current node and the candidate in the same cluster
					//cout << "\nFound: " << node.first << " and " << candidate << "\n";
					join(node.first, candidate);
				}
			}
		}
	}

	int size() { return static_cast<int>(graph_.size()); }

	int clusters() {
		int count{ 0 };
		for (auto const & n : graph_) {
			if (n.first == n.second) {
				count++;
			}
		}
		return count;
	}

	int nodes() { return static_cast<int>(graph_.size()); }

private:
	std::map<bits, bits, bitSort> graph_;

	std::vector<bits> neighbours(bits const & b) const {
		std::vector<bits> result;
		size_t len{ b.size() };
		// collect neighbours with hamming distance of 1
		bits argument{ b };
		for (size_t i{ 0 }; i < len; ++i) {
			result.push_back(argument.flip(i));
			argument = b;
		}
		// collect neighbours with hamming distance of 2
		for (size_t i{ 0 }; i < len; ++i) {
			argument = argument.flip(i);
			for (size_t j{ i + 1 }; j < len; ++j) {
				result.push_back(argument.flip(j));
				argument.flip(j);
			}
			argument.flip(i);
		}
		return result;
	};

	size_t distance(bits u, bits v) {
		return (u^v).count();
	}

	int rootDistance(bits u) {
		return static_cast<int>(distance(u, graph_.at(u)));
	}
};


struct edge {
	int u;
	int v;
	int cost;

	edge(int u_ = 0, int v_ = 0, int c_ = 0) {
		u = u_; v = v_; cost = c_;
	}
};

ostream& operator <<(ostream & os, edge e) {
	cout << e.u << " - " << e.v << " = " << e.cost;
	return os;
}

struct node {
	int name;
	int size;
	shared_ptr<node> p;
	explicit node(int n) : name{ n }, size{ 1 }, p{ nullptr } {};
	explicit node(int n, shared_ptr<node> parent) : name{ n }, size{ 1 + parent->size }, p{ parent } {};
};


shared_ptr<node> find2(shared_ptr<node> n) {
	if (n->p == n) return n;
	return find2(n->p);
}

shared_ptr<node> find(shared_ptr<node> n) {
	while (n->p != n) { n = n->p; }
	return n;
}

shared_ptr<node> join(shared_ptr<node> u, shared_ptr<node> v) {
	if (u->p != u || v->p != v) { cout << "Joining a non-root node (" << u->name << " and " << v->name << ")\n"; }
	if (u->size < v->size) {
		u->p = v;
		v->size += u->size;
		return v;
	}
	else {
		v->p = u;
		u->size += v->size;
		return u;
	}
}

bool join(map<int, shared_ptr<node>> & n, int u, int v) {
	auto uRoot{ find(n[u]) };
	auto vRoot{ find(n[v]) };
	if (uRoot == vRoot) return false;
	if (uRoot->size < vRoot->size) {
		uRoot->p = vRoot;
		uRoot->size += vRoot->size;
	}
	else {
		vRoot->p = uRoot;
		vRoot->size += uRoot->size;
	}
	return true;
}

ostream & operator<<(ostream & os, shared_ptr<node> node) {
	cout << node->name << "[size=" << node->size << ", ";
	if (node->p != node) {
		cout << " root=" << (node->p)->name;
	}
	else {
		cout << " *";
	}
	cout << "]\n";
	return os;
}

void show(map<int, shared_ptr<node>> const & nodes) {
	for (auto const & n : nodes) {
		cout << n.second;
	}
}

int getData(vector<edge> & g, set<int> & uniqueNodes) {
	/*
	[number_of_nodes]
	[edge 1 node 1] [edge 1 node 2] [edge 1 cost]
	[edge 2 node 1] [edge 2 node 2] [edge 2 cost]
	*/

	fstream fs;
	fs.open(R"(C:\Users\n419\Repos\Clustering\Problem1\cluster1.txt)");
	if (!(fs.is_open())) { cout << R"(Unable to open file)" << endl;  exit(-1); }

	string line;
	std::getline(fs, line);
	stringstream ss{ line };
	int nodes{ 0 };
	ss >> nodes;
	if (nodes == 0) { cout << R"(No data found)" << endl; exit(-2); }
	cout << nodes << " nodes expected\n";

	int i{ 0 };
	while (std::getline(fs, line)) {
		stringstream s{ line };
		int u{ 0 };
		int v{ 0 };
		int cost{ 0 };
		s >> u >> v >> cost;
		uniqueNodes.insert(u);
		uniqueNodes.insert(v);
		++i;
		g.emplace_back(u, v, cost);
	}
	cout << uniqueNodes.size() << " nodes loaded\n";
	cout << i << " edges loaded\n";
	//copy(g.cbegin(), g.cend(), ostream_iterator<edge>(cout, "\n"));
	return nodes;
}

bool operator<(edge const & lhs, edge const & rhs) {
	return lhs.cost > rhs.cost;
}

void secondGo() {
	fstream fs;
	fs.open(R"(C:\Users\n419\Repos\Clustering\Problem2\clusters2.txt)");
	string line;
	getline(fs, line);
	stringstream ss{ line };
	int len;
	ss >> len;
	cout << len << " nodes expected\n";
	UF graph;
	len = 0;
	while (getline(fs, line)) {
		line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
		bitset<24> bs{ line };
		graph.insert(bs);
		len++;
	}

	cout << "Read " << len << " lines " << graph.size() << " unique nodes loaded. Clusters = " << graph.clusters() << "\n";

	graph.clusterBy2();
	cout << "Clusters = " << graph.clusters() << endl;
	char c;
	cin >> c;
	return 0;
}

int main()
{
	vector<edge> G;
	set<int> V;
	int nCount{ getData(G,V) };

	int k{ nCount };
	int targetK{ 4 };

	map<int, shared_ptr<node>> nodes;
	for (auto const i : V) {
		auto n = make_shared<node>(i);
		n->p = n;
		nodes.emplace(n->name, n);
	}
	cout << nodes.size() << " nodes initialised\n";
	// All nodes are now initialised to be their own roots
	int lastCost;
	priority_queue<edge, vector<edge>, less<edge>> Q(G.begin(), G.end());


	while (!Q.empty() && k > targetK) {
		edge e{ Q.top() };
		lastCost = e.cost;
		Q.pop();
		if ((find(nodes[e.u]) != find2(nodes[e.u])) || (find(nodes[e.v]) != find2(nodes[e.v]))) {
			cout << "\n\nFind difference\n\n";
		};
		if (join(nodes, e.u, e.v)) {
			k--;
		}
	}
	cout << "Last cost = " << lastCost << endl;
	while (Q.top().cost == lastCost) Q.pop();
	cout << endl;
	cout << "\nk = " << k << " Maximum spacing = " << Q.top().cost << endl;
	cout << endl;
	
	secondGo();

}

