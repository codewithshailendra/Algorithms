#include <iostream>
#include "Graph.h"
#include "Dijkstra.h"
#include "BellmanFord.h"


const std::string t1{ R"(t1.txt)" };
const std::string t2{ R"(t2.txt)" };
const std::string t3{ R"(t3.txt)" };
const std::string g1{ R"(g1.txt)" };  //Negative loop
const std::string g2{ R"(g2.txt)" };  //Negative loop
const std::string g3{ R"(g3.txt)" };  //shortest path = -19
const std::string l{ R"(large.txt)" };

void test1() {
	using namespace std;
	cout << "t1\n";
	Graph G1(t1);
	cout << "t2\n";
	Graph G2(t2);
	cout << "t3\n";
	Graph G3(t3);
	cout << "g1\n";
	Graph G4(g1);
	cout << "g2\n";
	Graph G5(g2);
	cout << "g3\n";
	Graph G6(g3);
	cout << "Large\n";
	Graph G7(l);
}

void dijkstra(Graph & g, int source) {
	try
	{
		Dijkstra D(g, source);
		D.shortestPaths();
		D.printPaths();
		std::cout << std::endl;
	}
	catch (const std::runtime_error& e)
	{
		std::cout << "Error: " << e.what();
		return;
	}
}

int bellmanFord(Graph & g) {
	int sp{ none };
	for (int i{ 1 }; i < g.V(); ++i) {
		BellmanFord B(g, i);
		if (B.hasNegativeLoop()) {
			std::cout << "Graph has a negative loop from node " << i << std::endl;
			return none;
		}
		else {
			std::cout << "Node " << i << " complete\n";
		}
		if (B.shortestPath() < sp) {
			sp = B.shortestPath();
		}
	}
	return sp;
}

int main() {
	std::string data{ g3 };
	Graph G(data);
	int sp{ bellmanFord(G) };
	if (sp < none) {
		std::cout << "Shortest path in " << data << " = " << sp << "\n";
	}
	std::cout << "\nPress any key to continue\n" << std::endl;
	char c;
	std::cin >> c;

}