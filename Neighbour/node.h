#pragma once

struct Node
{
	double dist;
	int dest;

	Node(int n, double d) : dest{ n }, dist{ d } {};
};

class nodeCompare {
public:
	bool operator()(Node const & lhs, Node const & rhs) {
		if (lhs.dist == rhs.dist) {
			return lhs.dist > rhs.dist;
		}
		return lhs.dist > rhs.dist;
	}
};


