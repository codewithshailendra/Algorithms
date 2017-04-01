#pragma once
#include <memory>

struct Node
{
	long long value;
	std::shared_ptr<Node> front;
	std::shared_ptr<Node> back;

	Node(long long val, std::shared_ptr<Node> b) :
		value{ val },
		front{ nullptr },
		back{ b }
	{/*std::cout << "Node " << value << " created at " << this << " with back = " << back << "\n";*/
	}

	~Node() { /*std::cout << "Node " << value << " destructed\n";*/ }
};


typedef std::shared_ptr<Node> pNode;

