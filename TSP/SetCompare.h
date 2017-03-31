#pragma once
#include <set>

class SetCompare
{
public:
	bool operator()(std::set<int> const & lhs, std::set<int> const & rhs) const {
		return lhs.size() < rhs.size();
	}
};

