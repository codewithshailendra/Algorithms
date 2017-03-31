#pragma once
#include <vector>
#include <set>
#include <memory>
#include <iterator>
#include <algorithm>
#include <iostream>

class CombGen
{
public:
	static std::vector<std::set<int>> Combinations(int n, int k);
private:
	static int nextComb(std::shared_ptr<std::vector<int>> & comb, int n, int k);
};

