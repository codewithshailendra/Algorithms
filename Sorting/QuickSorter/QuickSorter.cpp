#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include "QuickSort.h"
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>

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

void dataTest() {
	vector<int> v;
	string line;
	string fname{ R"(C:\Users\n419\Repos\Algorithms\Sorting\QuickSorter\QuickSort.txt)" };
	ifstream dataFile(fname);
	if (dataFile.is_open()) {
		while (getline(dataFile, line)) {
			stringstream ss{ line };
			int ni;
			ss >> ni;
			v.push_back(ni);
		}
		dataFile.close();
		cout << "File input completed" << endl;
	}
	std::cout << "Sort started";
	QuickSort qs;
	qs.sort(v);
	std::cout << "Sort completed" << endl;
	if (is_sorted(v.cbegin(), v.cend())) {
		cout << "Random array of length " << v.size() << " sorted" << endl;
	}
	else {
		cout << "Error random array of length " << v.size() << " not sorted" << endl;
		cout << endl;
	}
}

void loopTest() {
	int n{ 1 };
	while (n++ < 64) {
		int loop{ 100 };
		bool OK{ false };
		while (loop--) {
			vector<int> v{ initialise(n) };
			//std::cout << "Sort started";
			QuickSort qs;
			qs.sort(v);
			//std::cout << "   Sort completed" << endl;
			OK = is_sorted(v.cbegin(), v.cend());
			if (!OK) break;
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
	//loopTest();
	dataTest();
	return 0;
}
