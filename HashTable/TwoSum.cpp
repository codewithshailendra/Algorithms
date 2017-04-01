#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include "HTable.h"
#include "HashFunctions.h"

using namespace std;
const string live{ R"(C:\Users\n419\Repos\HashTables\HashTables\data2sum.txt)" };
const string test{ R"(C:\Users\n419\Repos\HashTables\HashTables\test2sum.txt)" };
const string extract{ R"(C:\Users\n419\Repos\HashTables\HashTables\extract.txt)" };

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


int main()
{
	HTable<Jenkins> table(1000000);
	std::vector<long long> v; 
	getData(live, table,v);
	table.show();
	std::cout << "Results with custom hash table: Found " << runScan(table,v) << " results\n";
	
	/*
	unordered_set<long long> table;
	acquire(live, table, v);
	std::cout << table.size() << " entries in " << table.bucket_count() << " buckets with load factor of " << table.load_factor() << "\n";
	std::cout << vScan2(table, v) << " values found\n";
*/
	char c;
	std::cin >> c;
	return 0;
}

