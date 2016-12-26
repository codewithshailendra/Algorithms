#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <random>
#include "Stopwatch.h"

using namespace std;

long long counter{ 0 };

int median(int a, int b, int c) {
	if ((a < b) && (a < c)) return min(b, c);
	if ((b < c) && (b < a)) return min(a, c);
	return min(a, b);
}

double FastPower(double a, int b) {
	counter++;
	double c{ 0 };
	double ans{ 0 };
	if (b == 1) {
		return a;
	}
	else {
		c = a * a;
	}
	ans = FastPower(c, static_cast<int>(floor(b / 2)));
	if (b & 0x001) {
		return a * ans;
	}
	else {
		return ans;
	}
}

void fp() {
	string line;
	string fname{ R"(C:\Users\n419\Repos\Algorithms\Sorting\ScratchPad\ReadMe.txt)" };
	ofstream dataFile;
	dataFile.open(fname, ios::trunc);
	if (dataFile.is_open()) {
		double a{ 2.24 };
		int b{ 1 };
		while (b++ < 256) {
			counter = 0;
			double result{ FastPower(a,b) };

			dataFile << b << "," << counter << "\n";
		}
		dataFile.close();
	}
}

int main()
{
	int n{ 1000000 };
	int loopLength{ 1000000 };
	default_random_engine dre;
	uniform_int_distribution<int> uid(1, n);

	for (double alpha = 0; alpha < 0.5; alpha += 0.05) {
		int partition(alpha * n);
		int counter{ 0 };
		int loop{ loopLength };

		while (loop--) {
			if (uid(dre) >= partition) counter++;
		}
		double prob{ static_cast<double>(counter) / static_cast<double>(loopLength) };
		cout << "alpha = " << alpha << "  p(Index >= alpha = " << prob << endl;
	}

	return 0;
}

