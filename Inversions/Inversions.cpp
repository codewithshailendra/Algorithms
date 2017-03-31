#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include "iCounter.h"

using namespace std;

vector<int> initialise(size_t n) {
	auto tp{ chrono::system_clock::now() };
	auto seed{ static_cast<unsigned int>((tp.time_since_epoch()).count() % UINT16_MAX) };
	default_random_engine dre(seed);
	//default_random_engine dre;
	uniform_int_distribution<int> uid(0, 1000);
	vector<int> result;
	while (n--) result.push_back(uid(dre));
	return result;
}

vector<int> inverted(size_t n) {
	vector<int> result;
	while (n--) { result.push_back(static_cast<int>(n)); }
	return result;
}

void randomTest(int n) {
	iCounter<int> counter(initialise(n));
	auto i = counter.inversions();
	auto b = counter.brut();
	if (i != b) {
		cout << "Failed for random sequence of length " << n << "  Inversions = " << i << "   Bruteforce check = " << b << "  Difference = " << b - i << endl;
	}
	else {
		cout << "Completed random array of length " << n << endl;
	}
}

void invertTest(int n) {
	iCounter<int> counter(inverted(n));
	auto i = counter.inversions();
	auto b = counter.brut();
	int calc = n*(n - 1) / 2;
	if (i != calc) {
		cout << "Algorithm failed for length " << n << "  Inversions = " << i << "   n(n-1)/2 = " << calc << endl;
	}
	else {
		cout << "Algorithm completed length " << n << "   n(n-1)/2 = " << calc << endl;
	}
	if (b != calc) {
		cout << "Bruteforce failed for length " << n << "  Bruteforce = " << b << "   n(n-1)/2 = " << calc << endl;
	}
	else {
		cout << "Bruteforce completed length " << n << "   n(n-1)/2 = " << calc << endl;
	}
}

void dataTest() {
	vector<int> a;
	string line;
	string fname{ R"(C:\Users\n419\Repos\Algorithms\Sorting\InversionCounter\IntegerArray.txt)" };
	ifstream dataFile(fname);
	if (dataFile.is_open()) {
		while (getline(dataFile, line)) {
			stringstream ss{ line };
			int ni;
			ss >> ni;
			a.push_back(ni);
		}
		dataFile.close();
		cout << "File completed" << endl;
	}
	iCounter<int> counter(a);
	auto i = counter.inversions();
	cout << i << " inversions" << endl;
}

void loopTest() {
	int len{ -1 };

	while (len != 0) {
		cout << "\nlength? ";
		cin >> len;
		cout << endl;
		invertTest(len);
		randomTest(len);
	}
}

int main()
{
	dataTest();
	return 0;
}