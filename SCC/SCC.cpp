#include<iostream>
#include<fstream>
#include<string>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Graph.h"

const std::string c1{ R"(..\st2.txt)" };
const std::string c2{ R"(..\..\Data\sat1.txt)" };

const std::string l{ R"(..\SCC.txt)" };
const std::string t1{ R"(..\SCCTest.txt)" };
const std::string t{ R"(..\TinyDG.txt)" };


int main()
{
	Graph G(c2);
	//G.getReverseData();
	G.getReverseConstraints();
	std::cout << G.V() << " nodes and " << G.E() << " edges loaded in reverse\n";
	//std::cout << G.toString() << std::endl;
	G.reverseDFS();
	std::cout << "Reverse DFS completed\n";
	//G.getData();
	G.getConstraints();
	std::cout << G.V() << " nodes and " << G.E() << " edges loaded\n";
	//std::cout << G.toString() << std::endl;
	G.kccDFS();
	std::cout << "KCC DFS completed\n";
	G.clear();
	std::cout << "Dumped reverse adjacency list\n";
	int componentCount{ G.componentCount() };
	std::cout << "\n" << componentCount << " strongly connected components found\n";
	int top{ componentCount < 10 ? componentCount : 10 };
	std::cout << "\nResult ordered by component size\n";
	for (auto const & cc : G.topComponents(top)) {
		std::cout << cc.first << " nodes in component " << cc.second << "\n";
	}
	G.checkContraints();
	char c;
	std::cout << "\nPress any key to exit\n";
	std::cin >> c;
	return 0;
}

