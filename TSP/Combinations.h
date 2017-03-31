#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <string> 
#include <fstream>
#include <sstream>

using namespace std;

class Combinations {

public:
	Combinations() 
	{
	};

	Combinations(int n, int m) :
		inputLength_{ n }, comboLength_(m), count_{ 0 },
		combos_{ static_cast<int>(comb(inputLength_, comboLength_)) },
		set_{ std::vector<int>(inputLength_) },
		partial_(std::vector<int>(comboLength_)),
		out_{ std::make_unique<std::vector<std::set<int>>>(combos_, std::set<int>()) }
	{
		makeInputSet();
		generate(0, inputLength_ - 1, comboLength_ - 1);
		//std::cout << "n = " << n << "  m = " << m << std::endl;
	};

	// return all sets containing zero
	std::unique_ptr<std::vector<std::set<int>>>  getSets() {
		auto result = std::make_unique<std::vector<std::set<int >>>();
		for (auto const s : *out_) {
			if (s.count(0) != 0) {
				result->push_back(s);
			}
		}
		return result;
	}

	void show() {
		for (auto const & set : *out_)
		{
			for (auto const & v : set) {
				std::cout << v << ", ";
			}
			std::cout << std::endl;
		}
	}

	void show(int m) {
		string name{ R"(comb)" + std::to_string(m) + ".txt" };
		auto setVector = getSets();
		for (auto const & s : *setVector) {
			for (auto const & i : s) {
				cout << i << ", ";
			}
			cout << endl;
		}
	}

	int writeSet() {
		string name{ R"(comb)" + std::to_string(comboLength_) + ".txt" };
		cout << name << endl;
		ofstream fs;
		fs.open(name);
		if (!fs) {
			cout << "Unable to open " << name << " for writing" << endl;
			return -1;
		}
		for (auto const s : *out_) {
			if (s.count(0) == 0) { break; }
			for (auto const & i : s) {
				fs << i << " ";
			}
			fs << "\n";
		}

		fs.close();
		return static_cast<int>(out_->size());
	}

	std::unique_ptr<std::vector<std::set<int>>> readFile(int m) {
		auto result = std::make_unique<std::vector<std::set<int >>>();
		string name{ R"(comb)" + std::to_string(m) + ".txt" };
		std::cout << name << endl;
		ifstream ifs;
		ifs.open(name);
		if (!ifs.is_open()) {
			cout << "Unable to open " << " for reading" << name << endl;
			return result;
		}
		string line;
		while (getline(ifs, line)) {
			stringstream ss{ line };
			int i;
			set<int> nextSet{};
			while (ss >> i) {
				nextSet.insert(i);
			}
			result->push_back(nextSet);
		}
		ifs.close();
		return result;
	}

private:
	int inputLength_;
	int comboLength_;
	int count_;
	int combos_;

	std::vector<int> set_;
	std::vector<int> partial_;
	std::unique_ptr<std::vector<std::set<int>>> out_;

	void makeInputSet() {
		for (int i{ 0 }; i < inputLength_; ++i) {
			set_[i] = i;
		}
	};

	unsigned long long comb(unsigned long long n, unsigned long long k) {
		// this is from Knuth vol 3
		if (k > n) {
			return 0;
		}
		unsigned long long r = 1;
		for (unsigned long long d = 1; d <= k; ++d) {
			r *= n--;
			r /= d;
		}
		return r;
	}

	void generate(int i, int j, int m) {
		// combination of size m (number of slots) out of set[i..j]
		if (m > 0) {
			for (int z = i; z < j - m + 1; z++) {
				partial_[comboLength_ - m - 1] = set_[z]; // add element to permutation
				generate(z + 1, j, m - 1);
			}
		}
		else {
			// last position
			for (int z = i; z < j - m + 1; z++) {
				partial_[comboLength_ - m - 1] = set_[z];
				out_->at(count_++) = std::set<int>(partial_.cbegin(), partial_.cend()); // add set to output vector
			}
		}
	}

};