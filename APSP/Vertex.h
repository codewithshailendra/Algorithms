#pragma once
#include "GraphDefs.h"

struct Vertex
{
	int d;
	int pred;

	Vertex() :
		d{ inf }, pred{ none } {	};

	Vertex(int estimate, int predecessor) :
		d{ estimate }, pred{ predecessor } {	};
};

