#include <iostream>
#include <string>
#include <iterator>
#include <memory>
#include "Graph.h"

using namespace std;

const string t1{ R"(..\..\..\Data\nnTest.txt)" };
const string t2{ R"(..\..\..\Data\nnTest2.txt)" };
const string t{ R"(..\..\..\Data\nn.txt)" };

int main()
{
	Graph G(t);
	double distance{ G.calculate() };
	std::cout << "Minimum tour distance = " << fixed << distance << "\n";
	std::cout << "\nPress any key to exit\n";
	char c;
	std::cin >> c;
	return 0;
}

