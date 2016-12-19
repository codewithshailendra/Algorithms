#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include "iCounter.h"

using namespace std;

vector<int> initialise(size_t n) {
	auto tp{ chrono::system_clock::now() };
	auto seed{ static_cast<unsigned int>((tp.time_since_epoch()).count() % UINT16_MAX )};
	default_random_engine dre(seed);
	//default_random_engine dre;
	uniform_int_distribution<int> uid(0, 1000);
	vector<int> result;
	n = static_cast<size_t>(pow(2.0, n));
	while (n--) result.push_back(uid(dre));
	return result;
}

vector<int> inverted(size_t n) {
	vector<int> result;
	n = static_cast<size_t>(pow(2.0, n));
	while (n--) result.push_back(n);
	return result;
}

void randomTest(int nMax) {
	for (int N = 1; N < nMax; ++N) {
		for (int rep = 0; rep < 1000; ++rep) {
			iCounter<int> counter(initialise(N));
			auto i = counter.inversions();
			auto b = counter.brut();
			if (i != b) {
				cout << "[" << rep <<"] Failed for length " << pow(2.0, N) << "  Inversions = " << i << "   Bruteforce check = " << b << "  Difference = " << i-b << endl;
			}
		}
		cout << "Completed length " << pow(2.0, N) << endl;
	}
}

void invertTest(int nMax) {
	for (int N = 1; N < nMax; ++N) {
		iCounter<int> counter(inverted(N));
		auto i = counter.inversions();
		auto b = counter.brut();
		int n = static_cast<size_t>(pow(2.0, N));
		n = n*(n - 1) / 2;
		if (i != n) {
			cout << "Algorithm failed for length " << pow(2.0, N) << "  Inversions = " << i << "   n(n-1)/2 = " << n << endl;
		}
		if (b != n) {
			cout << "Bruteforce failed for length " << pow(2.0, N) << "  Bruteforce = " << b << "   n(n-1)/2 = " << n << endl;
		}
		cout << "Completed length " << pow(2.0, N) << "   n(n-1)/2 = " << n << endl;
	}
}

int main()
{
	//invertTest(12);
	randomTest(12);
	return 0;
}