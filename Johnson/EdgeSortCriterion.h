#pragma once
#include <functional>
class EdgeSortCriterion
{
public:
	bool operator()(std::pair<int, int> const & lhs, std::pair<int, int> const & rhs) {
		return (lhs.second > rhs.second);
	}
};

