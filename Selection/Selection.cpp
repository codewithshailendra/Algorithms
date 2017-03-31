#include "Selector.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

vector<int> initialise(size_t n) {
	auto seed{ static_cast<unsigned int>((chrono::system_clock::now()).time_since_epoch().count()) };
	default_random_engine dre(seed);
	uniform_int_distribution<int> uid(0, 1000);
	vector<int> result;
	n = static_cast<size_t>(pow(2.0, n));
	//std::cout << "initialising length " << n;
	while (n--) result.push_back(uid(dre));
	//std::cout << " completed " << endl;
	return result;
}


void stressTest() {
	size_t n{ 1 };
	while (n++ < 64) {
		int loop{ 100 };
		bool OK{ false };
		while (loop--) {
			vector<int> v{ initialise(n) };
			vector<int> checkVector{ v.cbegin(),v.cend() };
			sort(checkVector.begin(), checkVector.end());
			for (size_t i{ 0 }; i < n; ++i) {
				OK = (checkVector[i] == Selector<int>::nthOrder(v, i));
				if (!OK) break;
			}
		}
		if (OK) {
			cout << "Completed for length " << pow(2, n) << endl;
			cout << endl;
		}
		else {
			cout << "Error for length " << pow(2, n) << endl;
			cout << endl;
		}
	}
}

int main()
{
	vector<double> v{ 5,2,4,56,88,101,2,5,5.1,5.3,5.2,6,1,8 };
	copy(v.cbegin(), v.cend(), ostream_iterator<double>(cout, ", "));
	cout << endl;
	for (size_t i = 0; i < v.size(); ++i) {
		cout << "Order statistic " << i << " = " << Selector<double>::nthOrder(v, i) << endl;
	}

	cout << "\n\nStarting stress test\n";
	stressTest();

	return 0;
}

