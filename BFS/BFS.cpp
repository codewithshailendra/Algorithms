#include <iostream>
#include <algorithm>
#include <iterator>
#include <queue>
#include <vector>
#include <map>
#include <string>
#include "Node.h"
#include "Graph.h"

using namespace std;
using NodeQ = queue<Node>;

const string facebook{ R"(C:\Users\n419\Repos\Graphs\facebook.txt)" };
const string stanford{ R"(C:\Users\n419\Repos\Graphs\stanford.txt)" }; //Nodes: 281903 Edges: 2312497
const string alist{ R"(C:\Users\n419\Repos\Graphs\aList.txt)" };
const string pairs{ R"(C:\Users\n419\Repos\Graphs\test.txt)" };
const string SCC{ R"(C:\Users\n419\Repos\Graphs\SCC.txt)" };
const string SCC2{ R"(C:\Users\n419\Repos\Graphs\SCC2.txt)" };
const string SCCTest{ R"(C:\Users\n419\Repos\Graphs\SCCTest.txt)" };
const string connected{ R"(C:\Users\n419\Repos\Graphs\connected.txt)" };
const string directed{ R"(C:\Users\n419\Repos\Graphs\directed.txt)" };
const string dag{ R"(C:\Users\n419\Repos\Graphs\dag.txt)" };
const string cormen{ R"(C:\Users\n419\Repos\Graphs\cormenPage605.txt)" };
const string cormen3{ R"(C:\Users\n419\Repos\Graphs\cormenpage616.txt)" };
const string cormen2{ R"(C:\Users\n419\Repos\Graphs\cormenPage613.txt)" };
const string dasgupta{ R"(C:\Users\n419\Repos\Graphs\dasgupta102.txt)" };

int main()
{
	std::string fname{ SCC };
	std::cout << "Data file: " << fname << std::endl;
	Graph g2(fname);
	g2.SCC();
	std::cout << "\nEnter 1 to End " << std::endl;
	int i;
	std::cin >> i;
	return 0;
}

