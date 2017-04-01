#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "HTable.h"
#include "HashFunctions.h"

using namespace std;
const string live{ R"(C:\Users\n419\Repos\HashTables\HashTables\data2sum.txt)" };
const string test{ R"(C:\Users\n419\Repos\HashTables\HashTables\test2sum.txt)" };
const string extract{ R"(C:\Users\n419\Repos\HashTables\HashTables\extract.txt)" };

const string live2{ R"(C:\Users\n419\Repos\HashTables\HashTables\Median.txt)" };
const string test2{ R"(C:\Users\n419\Repos\HashTables\HashTables\extract.txt)" };

void getData(string name, HTable<Jenkins> & table, std::vector<long long> & v) {
	std::ifstream input(name);
	long long value{ 0 };
	if (input.is_open()) {
		while (input >> value) {
			table.Insert(value);
			v.push_back(value);
		}
	}
	input.close();
}

void getData2(string name, std::vector<int> & v) {
	std::ifstream input(name);
	int value{ 0 };
	if (input.is_open()) {
		while (input >> value) {
			v.push_back(value);
		}
	}
	input.close();
}

size_t runScan(HTable<Jenkins> & table, std::vector<long long> & v) {
	std::unordered_set<int> result;
	for (int t = -10000; t < 10001; ++t) {
		size_t index{ v.size() >> 1 };
		for (size_t i = 0; i < index; i++) {
			long long target{ t - v[i] };
			if (table.Contains(target)) {
				result.insert(t);
			}
		}
		if (t % 100 == 0) std::cout << "Target value = " << t << "  Results = " << result.size() << "\n";
	}
	return result.size();
}

void acquire(string name, unordered_set<long long> & table, std::vector<long long> & v) {
	std::ifstream input(name);
	long long value{ 0 };
	if (input.is_open()) {
		while (input >> value) {
			table.insert(value);
			v.push_back(value);
		}
	}
	input.close();
}

size_t scan(string name, unordered_set<long long> & table) {
	std::unordered_set<int> result;
	std::ifstream input(name);
	long long value{ 0 };
	if (input.is_open()) {
		while (input >> value) {
			for (int i = -10000; i < 10001; ++i) {
				long long target{ i - value };
				if (table.find(target) != table.cend()) {
					result.insert(i);
				}
			}
		}
	}
	input.close();
	return result.size();
}

size_t vScan(unordered_set<long long> & table, std::vector<long long> & v) {
	std::unordered_set<int> result;
	for (int t = -10000; t < 10001; ++t) {
		for (auto const & x : v) {
			long long target{ t - x };
			if ((t - x) != x) {
				if (table.find(t - x) != table.cend()) {
					result.insert(t);
				}
			}
			else {
				std::cout << ".";
			}
		}
		if (t % 100 == 0) std::cout << "\nTarget = " << t << "  Results = " << result.size() << "\n";
	}
	return result.size();
	// returns the correct result of 427
}

size_t vScan2(unordered_set<long long> & table, std::vector<long long> & v) {
	std::unordered_set<int> result;
	for (int t = -10000; t < 10001; ++t) {
		size_t index{ v.size() >> 1 };
		for (size_t i = 0; i < index; i++) {
			long long target{ t - v[i] };
			if (table.find(target) != table.cend()) {
				result.insert(t);
			}
		}
		if (t % 100 == 0) std::cout << "Target = " << t << "  Results = " << result.size() << "\n";
	}
	return result.size();
}

int median()
{
	std::vector<int> data;
	getData2(live, data);

	priority_queue<int, std::vector<int>, std::greater<int>> highHeap;
	priority_queue<int, std::vector<int>, std::less<int>> lowHeap;

	int msum{ 0 };

	auto it{ data.cbegin() };

	// make sure we have an entry in each heap to avoid an "if empty" condition in the main loop
	if (*it > *(it + 1)) {
		highHeap.push(*it);
		lowHeap.push(*(it + 1));
	}
	else {
		lowHeap.push(*it);
		highHeap.push(*(it + 1));
	}

	// don't forget to add the initial entries to the running sum
	msum = (msum + *it) % 10000;
	msum = (msum + lowHeap.top()) % 10000;

	it += 2;

	while (it != data.cend()) {
		if (*it > highHeap.top()) {
			highHeap.push(*it);
		}
		else {
			lowHeap.push(*it);
		}

		it++;

		if (highHeap.size() > lowHeap.size()) {
			lowHeap.push(highHeap.top());
			highHeap.pop();
		}  // HighHeap is never bigger than low heap
		else if (lowHeap.size() > highHeap.size() + 1) {
			highHeap.push(lowHeap.top());
			lowHeap.pop();
		} // lowheap size is never mode than one larger than highheap size

		  // median is on the low heap for n = even (from questions definition) and on the 
		  // largest heap for n = odd. However highheap can never be bigger than low heap so
		  // the median is always on the lowHeap.

		msum = (msum + lowHeap.top()) % 10000;
	}

	std::cout << "Result = " << msum << std::endl;

	return 0;
}

int main()
{
	HTable<Jenkins> table(1000000);
	std::vector<long long> v;
	getData(live, table, v);
	table.show();
	std::cout << "Results with custom hash table: Found " << runScan(table, v) << " results\n";

	/*
	unordered_set<long long> table;
	acquire(live, table, v);
	std::cout << table.size() << " entries in " << table.bucket_count() << " buckets with load factor of " << table.load_factor() << "\n";
	std::cout << vScan2(table, v) << " values found\n";
	*/


	median();

	return 0;
}

