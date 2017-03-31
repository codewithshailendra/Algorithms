
#include <iostream>
#include <random>
#include <algorithm>
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
	for (int n = 1; n < 16; ++n) {
		vector<int> a{ initialise(n) };
		//vector<int> a{ 1,3,2,4,5,6,7,8 };
		vector<int> b{ MSort<int>::sort(a) };
		if (std::is_sorted(b.cbegin(), b.cend())) {
			cout << "Array length " << b.size() << " sorted" << endl;
		}
		else {
			cout << "Error - Not sorted" << endl;;
		}
	}
	return 0;
}
