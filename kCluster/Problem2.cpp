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


int main()
{
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

