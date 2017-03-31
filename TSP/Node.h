#pragma once
#include <vector>

struct Node
{
public:

	int id;
	bool selected;
	std::vector<Node> children;

	Node(int v) : id{ v }, selected{ false }, children{} {};

};

