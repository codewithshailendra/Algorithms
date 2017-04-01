#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;


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

void getData(vector<edge> & g) {
	/*
	[number_of_nodes] [number_of_edges]
	[one_node_of_edge_1] [other_node_of_edge_1] [edge_1_cost]
	[one_node_of_edge_2] [other_node_of_edge_2] [edge_2_cost]
	*/fstream fs;
fs.open(R"(C:\Users\n419\Repos\Stfd2\Prim\edges.txt)");
if (!(fs.is_open())) { cout << R"(Unable to open file)" << endl;  exit(-1); }

string line;
std::getline(fs, line);
stringstream ss{ line };
int nodes{ 0 };
int edges{ 0 };
ss >> nodes >> edges;
if (nodes == 0 || edges == 0) { cout << R"(No data found)" << endl; exit(-2); }
cout << nodes << " nodes and " << edges << " edges found\n";

int i{ 0 };
while (std::getline(fs, line)) {
	stringstream s{ line };
	int u{ 0 };
	int v{ 0 };
	int cost{ 0 };
	s >> u >> v >> cost;
	// Note: This is an undirected graph so each edge must be entered in both directions
	g.emplace_back(u, v, cost);
	g.emplace_back(v, u, cost);
}

if (!(g.size() == edges * 2)) { cout << R"(Error reading jobs)" << endl; exit(-3); }

//copy(g.cbegin(), g.cend(), ostream_iterator<edge>(cout, "\n"));
}

int main()
{
	vector<edge> G;
	getData(G);

	set<int> V;
	for (auto const & e : G) {
		V.insert(e.u);
		V.insert(e.v);
	}

	set<int> X;
	X.insert(*V.begin());
	V.erase(V.begin());

	vector<edge> T;

	while (!V.empty()) {
		edge next;
		int minCost{ INT_MAX };
		for (auto const & e : G) {
			if ((X.find(e.u) != X.cend() && V.find(e.v) != V.cend())) {
				//cout << e.cost << endl;
				if (e.cost < minCost) {
					next = e;
					minCost = e.cost;
				}
			}
		}
		T.push_back(next);
		X.insert(next.v);
		V.erase(next.v);
	}

	//cout << "\nMST is: \n";
	//copy(T.cbegin(), T.cend(), ostream_iterator<edge>(cout, "\n"));
	cout << "MST cost is: ";
	int MSTCost{ 0 };
	for (auto const& e : T) {
		MSTCost += e.cost;
	}
	cout << MSTCost << endl;

	return 0;
}

