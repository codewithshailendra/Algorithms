#pragma once
#include <set>

class SetHash
{
public:

	SetHash(std::set<int> set, int prevVert) : vertices_{ set }, vertex_{prevVert}
	{
	}

	bool operator=(SetHash & rhs) {
		if (vertex_ != rhs.vertex_) { return false; }
		std::cout << "SetHash returning a placeholder\n";
		return true;
	}
	
private:
	int vertex_;
	std::set<int> vertices_;
};

