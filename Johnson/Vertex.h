#pragma once
#include "GraphDefs.h"

struct Vertex
{
	int n;
	int d;
	int pred;

	Vertex() : n{ none }, d{ inf }, pred{ none } {	};
	Vertex(int node) : n{ node }, d{ inf }, pred{ none } {	};
	Vertex(int node, int estimate, int predecessor) :
		n{ node }, d{ estimate }, pred{ predecessor } {	};
};

