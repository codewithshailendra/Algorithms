#pragma once
#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>

#include "SetCompare.h"

class ComboGen
{
public:

	static std::vector<std::set<int>> getCombinations(int n) {
		std::vector<std::set<int>> allSets; 
		if (n == 1) {
			allSets.push_back(std::set<int>({ 1 }));
		}
		std::vector<int> input(n);
		for (int i{ 0 }; i < n; i++) {
			input[i] = i + 1;
		}
		std::vector<int> result(n, 0);
		generate(input, 0, 0, allSets, result);
		std::sort(allSets.begin(), allSets.end(), SetCompare());
		return allSets;
	}

	static void show(int n) {
		std::cout << std::endl << "n = " << n ;
		auto v = getCombinations(n);
		for (auto const & s : v) {
			std::copy(s.cbegin(), s.cend(), std::ostream_iterator<int>(std::cout, ", "));
			std::cout << std::endl;
		}
	}

private:

	// return a set containing the first pos elements of input
	static std::set<int> createSet(std::vector<int> input, int pos) {
		if (pos == 0) {
			return std::set<int>();
		}
		std::set<int> results;
		for (int i = 0; i < pos; i++) {
			results.insert(input[i]);
		}
		return results;
	}

	static 	void generate(std::vector<int> input, int start, int pos, std::vector<std::set<int>> & allSets, std::vector<int> result) {
		if (pos == input.size()) {
			return;
		}
		std::set<int> newSet = createSet(result, pos);
		allSets.push_back(newSet);
		for (int i = start; i < input.size(); i++) {
			result[pos] = input[i];
			generate(input, i + 1, pos + 1, allSets, result);
		}
	}

};

