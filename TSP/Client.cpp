#include <string>
#include <iterator>
#include "Graph.h"
#include "TSPI.h"
#include "Combinations.h"

using namespace std;

const string t1{ R"(tsp.txt)"};


int main()
{

	//Graph G(t1);
	Graph G;
	TSPI tsp(G,1);
	std::cout << "Minimum tour distance = " << tsp.distance() << "\n";
	std::cout << "Correct result is 21\n";
	char c;

	std::cin >> c;
    return 0;
}

