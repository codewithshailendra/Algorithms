#pragma once
#include <memory>
#include <numeric>
#include <vector>
#include <iostream>
#include "Node.h"
#include "HashFunctions.h"

template <typename hash>
class HTable
{
public:
	HTable(size_t initialCapacity) : table{ std::make_unique<pNode[]>(initialCapacity) }, capacity{ initialCapacity }, counts{} {
		size_t i{ 0 };
		while (initialCapacity--) { table[i++] = nullptr; }
	};

	void Insert(long long val) {
		unsigned int key{ hash::Hash(val) };
		auto newNode = std::make_shared<Node>(val, table[key]);
		if (table[key] != nullptr) {
			table[key]->front = newNode;
		}
		table[key] = newNode;
	}

	// returns true if value is present in the hashtable
	bool Contains(long long val) const {
		unsigned int key{ hash::Hash(val) }; 
		pNode n{ table[key] };
		while (n) {
			if (n->value == val) return true;
			n = n->back;
		}
		return false;
	}

	void Remove(long long val) {
		pNode& n{ table[hash::Hash(val)] };
		while (n) {
			if (n->value == val) {
				if (n->back) { (n->back)->front = n->front; }
				if (n->front) {
					(n->front)->back = n->back;
					return;
				}
				else { //  I'm the front node so make table[key] entry = my back node
					n = n->back;
					return;
				}
			}
			n = n->back;
		}
	}

	void show() {
		counts.clear();
		for (size_t j = 0; j < capacity; ++j) {
			pNode n{ table[j] };
			if (n) {
				int entries{ 0 };
				while (n) {
					entries++;
					n = n->back;
				}
				counts.push_back(entries);
			}
		}
		std::cout << counts.size() << " of " << capacity << " buckets occupied so alpha = " << counts.size() / (float)capacity << ". Average bucket population = " << std::accumulate(counts.cbegin(), counts.cend(), 0) / (float)counts.size() << "\n";
	}
	~HTable() {}

private:
	std::unique_ptr<pNode[]> table;
	size_t capacity;
	std::vector<int> counts;

};

