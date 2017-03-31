#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <iterator>
#include <map>
#include <chrono>
#include <set>

using namespace std;
const string l1{ R"(knapsack1.txt)" };
const string l2{ R"(knapsack2.txt)" };
const string t{ R"(test1.txt)" };

class Opt {

public:
	Opt(vector<int> V, vector<int> W, int C) :
		M{}, N{ static_cast<int>(values.size() - 1) }, values{ V }, weights{ W }, capacity{ C }, optValue{ 0 }, calcs{} {
		// rows are objects columns are weights
		for (int n{ 0 }; n < N + 1; ++n) {
			cout << n << "\n";
			M[n].emplace(0, 0);
			for (int w{ 1 }; w < capacity + 1; w++) {
				M[n].emplace(w, -1);
			}
		}
	};

	int subsetSum() {
		auto start1 = chrono::system_clock::now();
		int ret = ssSum(N, capacity);
		int optimum = M[N].find(capacity)->second;;
		cout << "Optimum value is " << optimum << "\n";
		auto stop1 = chrono::system_clock::now();
		auto diff = chrono::duration_cast<chrono::milliseconds> ((stop1 - start1));
		cout << "Recursive version completed in " << diff.count() << " miliseconds\n";
		//cout << "Hits = " << memoHit << "  Misses = " << memoMiss << endl; // << " distinct values = " << calcs.size() << endl;
		//copy(calcs.cbegin(), calcs.cend(), ostream_iterator<int>(cout, ", "));
		return optimum;
	}

	void objects() {};

private:
	map<int, map<int, int>> M;
	vector<vector<int>> A;
	vector<int> values;
	vector<int> weights;
	int capacity;
	int N;
	int optValue;
	int memoHit{ 0 };
	int memoMiss{ 0 };
	set<int> calcs;

	int ssSumRef(int n, int capacity) {
		if (n == 0 || capacity == 0) {
			return 0;
		}
		if (M[n].find(capacity) != M[n].cend()) {
			//cout << "Hit at " << n << " " << capacity << "\n";
			return M[n].find(capacity)->second;
		}

		for (int i{ 1 }; i < n + 1; ++i) {
			for (int w{ 1 }; w < capacity + 1; ++w) {
				int last{ ssSum(i - 1, w) };
				if (w < weights[i]) {
					M[i][w] = last;
					//cout << i << "," << w << " = " << M[i][w] << "  last\n";
				}
				else {
					int next{ ssSum(i - 1,w - weights[i]) + values[i] };
					M[i][w] = (next > last) ? next : last;
					//cout << i << "," << w << " = " << M[i][w] << "  last = " << last << "  next= "  << next << "  value = " << values[i] << "\n";
				}
			}
		}
		return M[n][capacity];
	}

	int ssSum(int n, int capacity) {

		if (n == 0 || capacity == 0) {return 0;}
		
		if (M[n][capacity] >= 0) {
			//cout << "Hit at " << n << " " << capacity << "\n";
			//memoHit++;
			return M[n][capacity];
		}

		for (int i{ 1 }; i < n + 1; ++i) {
			for (int w{ 1 }; w < capacity + 1; ++w) {
				int last{ ssSum(i - 1, w) };
				if (w < weights[i]) {
					M[i][w] = last;
					//cout << i << "," << w << " = " << M[i][w] << "  last\n";
				}
				else {
					int next{ ssSum(i - 1,w - weights[i]) + values[i] };
					//memoMiss++;
					//calcs.insert(w - weights[i]);
					M[i][w] = (next > last) ? next : last;
					//cout << i << "," << w << " = " << M[i][w] << "  last = " << last << "  next= "  << next << "  value = " << values[i] << "\n";
				}
			}
		}

		return M[n][capacity];
	}
};


int getData(string fname, vector<int> & v, vector<int> & w) {
	/*
	[knapsack_size][number_of_items]
	[value_1] [weight_1]
	[value_2] [weight_2]
	*/
	fstream fs;
	fs.open(fname);
	if (!fs.is_open()) return -1;
	int N{ 0 };
	int capacity{ 0 };
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
	return capacity;
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

int iterative(vector<int> & v, vector<int> & w, int & W) {

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

	auto start1 = chrono::system_clock::now();

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
	--I; --X;
	cout << "Optimal value = " << A[X].at(I) << "\n";
	auto stop1 = chrono::system_clock::now();
	auto diff = chrono::duration_cast<chrono::milliseconds> ((stop1 - start1));
	cout << "Iterative version completed in " << diff.count() << " miliseconds\n";

	//while (I > 0 && X > 0) {
	//	while (I > 0 && (A[X].at(I) == A[X].at(I - 1))) {
	//		I--;
	//	}
	//	if (I > 0) {
	//		cout << "Object " << I << endl;
	//		X = (w[I] > X) ? 0 : X - w[I];
	//		I--;
	//	}
	//}

	return A[X].at(I);
}

class Opt2 {

public:
	Opt2(vector<int> V, vector<int> W, int C) :
		memo(C+1), N{ static_cast<int>(values.size()-1) }, values{ V }, weights{ W }, capacity{ C }, optValue{ 0 }, calcs{} {
	};

	int subsetSum() {
		int next;
		auto start1 = chrono::system_clock::now();
		for (auto & m : memo) { m = 0; }
		// Bottom-up : start at zero and calculate the next value in terms of the current value
		for (int i{ 0 }; i < N+1; ++i) {
			vector<int> subproblem(capacity+1);
			for (int cap{0 }; cap < capacity + 1; ++cap) {
				if (cap < weights[i]) {
					subproblem[cap] = (memo[cap]);
				}
				else {
					next = memo[cap - weights[i]] + values[i];
					subproblem[cap] = (( memo[cap] > next)? memo[cap] : next);
				}
			}
			copy(subproblem.cbegin(), subproblem.cend(), memo.begin());
		}
		int optimum = memo[memo.size()-1];
		auto stop1 = chrono::system_clock::now(); 
		cout << "Optimum value is " << optimum << "\n";
		auto diff = chrono::duration_cast<chrono::milliseconds> ((stop1 - start1));
		cout << "Recursive version completed in " << diff.count() << " miliseconds\n";
		//cout << "Hits = " << memoHit << "  Misses = " << memoMiss << endl; // << " distinct values = " << calcs.size() << endl;
		//copy(calcs.cbegin(), calcs.cend(), ostream_iterator<int>(cout, ", "));
		return optimum;
	}

	void objects() {};

private:
	vector<int> memo;
	vector<int> values;
	vector<int> weights;
	int capacity;
	int N;
	int optValue;
	int memoHit{ 0 };
	int memoMiss{ 0 };
	set<int> calcs;
};



int main()
{
	// Using a brute force approach the result for knapsack2.txt should be: 4243395
	vector<int> v;
	vector<int> w;
	int W{ getData(l2, v, w) };
	assert(w.size() > 0); assert(w.size() == v.size());
	//cout << "\nIterative version\n";
	//int optimum{ iterative(v, w, W) };
	cout << "\nRecursive version initialising\n";
	Opt2 opt(v, w, W);
	cout << "\nRecursive version running\n";
	opt.subsetSum();
	cout << "\nPress any key to continue" << endl;
	char c;
	cin >> c;
	return 0;
}

