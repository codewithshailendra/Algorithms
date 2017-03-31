#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;
const string l{ R"(mwis.txt)" };
const string t{ R"(test.txt)" };

vector<int> getData(string const & fname) {
	fstream fs;
	fs.open(fname);
	string line;
	getline(fs, line);
	stringstream ss{ line };
	cout << line << " nodes expected\n";
	vector<int> data;
	while (getline(fs, line)) {
		ss.clear();
		ss.str(line);
		int weight;
		ss >> weight;
		data.push_back(weight);
	}
	fs.close();
	cout << data.size() << " nodes loaded" << endl;
	return data;
}

int main() {
	vector<int> w{ getData(l) };
	w.insert(w.begin(), 0);
	vector<int> A(w.size());
	A[0] = 0;
	A[1] = w[1];

	vector<vector<int>> check(w.size());
	check[1].push_back(1);

	for (size_t i{ 2 }; i < w.size(); ++i) {
		if (A[i - 1] > A[i - 2] + w[i]) {
			A[i] = A[i - 1];
			check[i] = vector<int>(check[i - 1]);
		}
		else {
			A[i] = A[i - 2] + w[i];
			// for equal value include node i
			vector<int> v{ check[i - 2] };
			v.push_back(i);
			check[i] = v;
		}
	}

	//cout << "Data : ";
	//copy(data.cbegin(), data.cend(), ostream_iterator<int>(cout, ", "));
	//cout << endl;
	//cout << "Sub-problems : ";
	//copy(A.cbegin(), A.cend(), ostream_iterator<int>(cout, ", "));
	//cout << endl;

	vector<int> solution;
	int i{ static_cast<int>(A.size()) - 1 };
	while (i > 1) {
		//cout << "i = " << i << "  sub-prob[" << i - 2 << "] = " << A[i - 2] << "  data [" << i << "] = " << data[i] << "  sub-prob[" << i - 1 << "] = " << A[i - 1] << endl;
		if (A[i - 1] >= (A[i - 2] + w[i])) {
			i--;
		}
		else {
			solution.push_back(i);
			i -= 2;
		}
	}

	// if node 2 wasn't include then node 1 must have been included and visa versa
	if (find(solution.cbegin(), solution.cend(), 2) == solution.cend()) {
		solution.push_back(1);
	}

	reverse(solution.begin(), solution.end());

	if (solution.size() != check[check.size() - 1].size()) {
		cout << " Different size solutions \n";
	}
	else {
		for (size_t i{ 0 }; i < solution.size(); ++i) {
			if (check[check.size() - 1][i] != solution[i]) {
				cout << check[check.size() - 1][i] << "  : " << solution[i] << "\n";
			}
		}
		cout << endl;
	}

	/*cout << "\nSolution : " << A[A.size() - 1] << "\n";
	copy(solution.cbegin(), solution.cend(), ostream_iterator<int>(cout, "\n"));
	cout << endl;*/

	vector<int> testCases{ 1, 2,3,4,17,117,517,997 };
	for (auto const t : testCases) {
		if (find(solution.cbegin(), solution.cend(), t) != solution.cend()) {
			cout << 1;
		}
		else {
			cout << 0;
		}
	}
	cout << endl;
	return 0;
}
