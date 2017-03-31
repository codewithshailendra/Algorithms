#include <string>
#include <iterator>
#include "Graph.h"
#include "TSP.h"
#include "Combinations.h"
#include <iostream>
#include <string>
#include <iterator>
#include <memory>
#include "Graph.h"

using namespace std;

const string t1{ R"(..\..\..\Data\tsp.txt)" };
const string t1{ R"(..\..\..\Data\nnTest.txt)" };
const string t2{ R"(..\..\..\Data\nnTest2.txt)" };
const string t{ R"(..\..\..\Data\nn.txt)" };

int main()
{

	Graph G(t1);
	TSP tsp(G, 1);
	std::cout << "Minimum tour distance = " << tsp.distance() << "\n";
	std::cout << "Correct result is 26442\n";

	Graph G2(t);
	double distance{ G2.calculate() };
	std::cout << "Minimum tour distance = " << fixed << distance << "\n";
	std::cout << "\nPress any key to exit\n";
	char c;
	std::cin >> c;
	return 0;


}

