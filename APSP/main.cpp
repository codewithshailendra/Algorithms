#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include "SimpleGraph.h"
#include "BellmanFord.h"
#include "Dij.h"

using namespace std;

const string t1{ R"(t1.txt)" };
const string d1{ R"(DijkstraTest.txt)" };
const string g1{ R"(g1.txt)" };
const string g2{ R"(g2.txt)" };
const string g3{ R"(g3.txt)" };

int main()
{
	auto G = std::make_shared<SimpleGraph>(d1);
	Dij D(G, 1);
	std::cout << "Dijkstra: " << D.shortestPath(4);
	std::cout << endl;
	D.printPath(4);
	std::cout << endl;
	auto BF = BellmanFord(G, 1);
	std::cout << "Bellman Ford: " << BF.shortestPath(4);
	std::cout << endl;
	BF.printPath(4);
	std::cout << endl;
	char c;
	std::cin >> c;
	return 0;
}

