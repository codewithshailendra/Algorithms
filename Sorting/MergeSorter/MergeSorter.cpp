
#include <iostream>
#include <random>
#include <algorithm>
#include "MSort.h"

using namespace std;

vector<int> initialise(std::size_t n) {
	default_random_engine dre;
	uniform_int_distribution<int> uid(0, 1000);
	vector<int> result;
	n = static_cast<std::size_t>(pow(2.0, n));
	while (n--) result.push_back(uid(dre));
	return result;
}

int main()
{
	//for (int n = 1; n < 16; ++n) {
		//vector<int> a{ initialise(n) };
		vector<int> a{5, 3, 8, 9, 1, 7, 0, 2, 6, 4 };
		vector<int> b{ MSort<int>::sort(a) };
		if (std::is_sorted(b.cbegin(), b.cend())) {
			cout << "Array length " << b.size() << " sorted" << endl;
		}
		else {
			cout << "Error - Not sorted" << endl;;
		}
	//}
	return 0;
}
