#include <string>
#include <iterator>
#include "Graph.h"
#include "TSP.h"
#include "Combinations.h"

using namespace std;

const string t1{ R"(..\..\..\Data\tsp.txt)" };


int main()
{

	Graph G(t1);
	TSP tsp(G, 1);
	std::cout << "Minimum tour distance = " << tsp.distance() << "\n";
	std::cout << "Correct result is 26442\n";
	char c;
	std::cin >> c;
	return 0;
}

