#include <iostream>
#include <array>
#include <vector>
#include <random>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
#include "Stopwatch.h"
#include "MSort.h"

using namespace std;

vector<int> initialise(size_t n) {
	default_random_engine dre;
	uniform_int_distribution<int> uid(0, 1000);
	vector<int> result;
	n = static_cast<size_t>(pow(2.0, n));
	while (n--) result.push_back(uid(dre));
	return result;
}

int main()
{
	size_t m{ 3 };
	Stopwatch sw;
	for (int n = 1; n < 16; ++n) {
		vector<int> a{ initialise(n) };
		sw.start();
		MSort<int> msorter;
		vector<int> b{ msorter.sort(a) };
		sw.stop();
		if (std::is_sorted(b.cbegin(), b.cend())) {
			cout << "Array length " << b.size() << " sorted in " << sw.display() << endl;
		}
		else {
			cout << "Error - Not sorted" << endl;;
		}
	}
	return 0;
}

