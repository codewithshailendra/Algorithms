#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <iterator>

using namespace std;
const string l{ R"(knapsack1.txt)" };
const string l2{ R"(C:\Users\n419\Repos\DProg\DP2\knapsack2.txt)" };
const string t{ R"(test1.txt)" };

int getData(string fname, vector<int> & v, vector<int> & w, int & capacity) {
	/*
	[knapsack_size][number_of_items]
	[value_1] [weight_1]
	[value_2] [weight_2]
	*/
	fstream fs;
	fs.open(fname);
	if (!fs.is_open()) return -1;
	int N{ 0 };
	string line;
	getline(fs, line);
	stringstream ss{ line };
	ss >> capacity >> N;
	cout << "Capacity = " << capacity << "  Number of items = " << N << "\n";
	int vv{ 0 };
	int ww{ 0 };
	// base weights and values from 1 to align with memotable
	v.push_back(0);
	w.push_back(0);
	while (getline(fs, line)) {
		ss.clear(); ss.str("");
		ss.str(line);
		ss >> vv >> ww;
		v.push_back(vv);
		w.push_back(ww);
	}
	if (v.size() != N + 1 || w.size() != N + 1) { cout << "Input error"; return 0; }
	return static_cast<int>(v.size());
}

void show(vector<vector<int>> const & A) {
	cout << "\n";
	for (int x{ static_cast<int>(A.size()) - 1 }; x >= 0; --x) {
		for (int i{ 0 }; i < A[0].size(); ++i) {
			cout << "\t" << x << "," << i << "\t" << A[x].at(i);
		}
		cout << endl;
	}
}

vector<int> extract(vector<vector<int>> const & A) {
	vector<int> res;
	cout << "\n";
	for (int x{ static_cast<int>(A.size()) - 1 }; x >= 0; --x) {
		for (int i{ 0 }; i < A[0].size(); ++i) {
			cout << "\t" << x << "," << i << "\t" << A[x].at(i);
		}
		cout << endl;
	}
	return res;
}

int main()
{
	// The result for knapsack1.txt is: 2493893

	vector<int> v;
	vector<int> w;
	int N{ 0 };
	int W{ 0 };
	N = getData(l2, v, w, W);
	assert(N > 0);
	//W = 10;
	//cout << "Warning W is patched for testing\n";
	// 2-D table where rows are residual capacity, columns are items and cells are values

	// memo table has rows = capacity of the rucksack + a zero row
	// so, if W = 6 there are 7 rows
	int X{ W + 1 };

	// memo table has columns = number items + a zero row
	// weights vector has been based from 1 so this is already accounted for
	// so, if there are 4 objects I should be 5
	int I{ static_cast<int>(w.size()) };

	vector<vector<int>> A;
	vector<int> firstRow(I, 0);
	A.push_back(firstRow);
	for (size_t i{ 1 }; i < X; ++i) {
		vector<int> row(I);
		row[0] = 0;
		A.push_back(row);
	}

	int offset{ 0 };
	int noChange{ 0 };
	int changed{ 0 };
	int result{ 0 };


	for (int i{ 1 }; i < I; ++i) {
		for (int x{ 1 }; x < X; ++x) {
			if (x < w[i]) { // the residual capacity is less than the weight of the next object
				result = A[x].at(i - 1);
			}
			else {
				offset = x - w[i]; // which we know to be at most 0
				noChange = A[x].at(i - 1);
				changed = A[offset].at(i - 1) + v[i];
				if (changed > noChange) {
					result = changed;
				}
				else {
					result = noChange;
				}
			}
			A[x].at(i) = result;
		}
	}


	//show(A);

	--I; --X;
	cout << "\nOptimal value = " << A[X].at(I) << "\n";
	cout << "Press any key to exit \n";
	char c;
	cin >> c;

	while (I > 0 && X > 0) {
		while (I > 0 && (A[X].at(I) == A[X].at(I - 1))) {
			I--;
		}
		if (I > 0) {
			cout << "Object " << I << endl;
			X = (w[I] > X) ? 0 : X - w[I];
			I--;
		}
	}

	return 0;
}

