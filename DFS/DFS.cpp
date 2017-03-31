#include<iostream>
#include<fstream>
#include<string>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include "DiGraph.h"
#include "DFSPaths.h"
#include "KSCC.h"

const std::string l{ R"(..\SCC.txt)" };
const std::string t1{ R"(..\SCCTest.txt)" };
const std::string t{ R"(..\TinyDG.txt)" };


int main()
{
	DiGraph dg(l);
	//std::cout << dg.toString() << std::endl;
	KSCC cc(dg);
	int c{ cc.count() };
	std::cout << c << " components\n";
	std::map<int, std::vector<int>> components;
	for (int i{ 0 }; i < c; ++i) {
		components.emplace(i, std::vector<int>());
	}
	for (int const & v : dg.nodes()) {
		components.at(cc.id(v)).push_back(v);
	}
	//for (auto const & component : components) {
	//	std::cout << component.first << " : ";
	//	std::copy(component.second.cbegin(), component.second.cend(), std::ostream_iterator<int>(std::cout, ", "));
	//	std::cout << std::endl;
	//}
	std::cout << "\nComponent counts\n";
	for (auto const & component : cc.Counts()) {
		std::cout << component.first << " : " << component.second << std::endl;
	}
	std::cout << std::endl;
	return 0;
}

