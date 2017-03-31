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
#include <iterator>

using namespace std;

struct node {
	int size;
	int p;
	node(int parent, int s) : size{ s }, p{ parent } {};
};

using ufMap = map<int, node>;

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

ostream & operator<<(ostream & os, node n) {
	cout << " [size=" << n.size << ", root=" << n.p << "]\n";
	return os;
}

void show(map<int, shared_ptr<node>> const & nodes) {
	for (auto const & n : nodes) {
		cout << n.first << " " << n.second;
	}
}

void getData(vector<edge> & g, ufMap & ufNodes) {
	/*
	[number_of_nodes]
	[edge 1 node 1] [edge 1 node 2] [edge 1 cost]
	[edge 2 node 1] [edge 2 node 2] [edge 2 cost]
	*/

	fstream fs;
	fs.open(R"(C:\Users\n419\Repos\Clustering\UF\cluster1.txt)");
	if (!(fs.is_open())) { cout << R"(Unable to open file)" << endl;  exit(-1); }

	string line;
	std::getline(fs, line);
	stringstream ss{ line };
	int nodes{ 0 };
	ss >> nodes;
	if (nodes == 0) { cout << R"(No data found)" << endl; exit(-2); }
	cout << nodes << " nodes expected\n";

	while (std::getline(fs, line)) {
		stringstream s{ line };
		int u{ 0 };
		int v{ 0 };
		int cost{ 0 };
		s >> u >> v >> cost;
		g.emplace_back(u, v, cost);
		ufNodes.emplace(u, node(u, 1));
		ufNodes.emplace(v, node(v, 1));
	}
}

void getData2(vector<edge> & g, ufMap & ufNodes) {
	/*
	[number_of_nodes]
	[edge 1 node 1] [edge 1 node 2]
	[edge 2 node 1] [edge 2 node 2]
	*/

	fstream fs;
	fs.open(R"(C:\Users\n419\Repos\Clustering\UF\mediumUF.txt)");
	if (!(fs.is_open())) { cout << R"(Unable to open file)" << endl;  exit(-1); }

	string line;
	std::getline(fs, line);
	stringstream ss{ line };
	int nodes{ 0 };
	ss >> nodes;
	if (nodes == 0) {
		cout << R"(No data found)" << endl;
		exit(-2);
	}
	cout << nodes << " nodes expected\n";

	while (std::getline(fs, line)) {
		stringstream s{ line };
		int u{ 0 };
		int v{ 0 };
		int cost{ 1 };
		s >> u >> v;
		g.emplace_back(u, v, cost);
		ufNodes.emplace(u, node(u, cost));
		ufNodes.emplace(v, node(v, cost));
	}
}

bool operator<(edge const & lhs, edge const & rhs) {
	return lhs.cost > rhs.cost;
}

int find(ufMap const & uf, int u) {
	while (u != uf.at(u).p) { u = uf.at(u).p; }
	return u;
}

bool join(ufMap & uf, int u, int v) {
	int uP{ find(uf,u) };
	int vP{ find(uf,v) };
	if (uP == vP) {
		//cout << "False " << uP << " and " << vP << "\n";
		return false;
	}
	if (uf.at(uP).size < uf.at(vP).size) {
		uf.at(uP).p = vP;
		uf.at(vP).size += uf.at(uP).size;
		//cout << "Put " << uP << " under " << vP << " so the root of " << uP << " is " << find(uf, uP) << "\n";
	}
	else {
		uf.at(vP).p = uP;
		uf.at(uP).size += uf.at(vP).size;
		//cout << "Put " << vP << " under " << uP << "\n";
	}
	return true;
}

int main()
{
	vector<edge> G;
	ufMap V;
	getData(G, V);
	priority_queue<edge, vector<edge>, less<edge>> Q(G.begin(), G.end());

	int eCount{ static_cast<int>(Q.size()) };
	int nCount{ static_cast<int>(V.size()) };
	cout << nCount << " nodes loaded\n";
	cout << eCount << " edges loaded\n";
	int k{ nCount };
	edge e;
	while (!Q.empty() && k >= 4) {
		e = Q.top();
		Q.pop();
		if (join(V, e.u, e.v)) {
			k--;
		}
	}


	cout << "Last edge cost was " << e.cost << endl;

	// 106 may have been correct

	return 0;
}

