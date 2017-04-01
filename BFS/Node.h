#pragma once
#include <vector>
#include <memory>

using Serial = size_t;
using Adjacencies = std::shared_ptr<std::vector<Serial>>;

enum Status { White, Gray, Black };

struct Node
{
	Serial id;
	bool done;
	Serial pred;
	Serial leader;
	Serial pre;
	Serial post;
	Adjacencies adj;

	Node() : id{ 0 }, done{ false }, pre{ 0 }, post{ 0 } {
		adj = std::make_shared<std::vector<Serial>>();
	}
	explicit Node(Serial i) : id{ i }, done{ false }, pre{ 0 }, post{ 0 } {
		{
			adj = std::make_shared<std::vector<Serial>>();
		}
	}
	Node(Serial i, Serial a) : id{ i }, done{ false }, pre{ 0 }, post{ 0 } {
		adj = std::make_shared<std::vector<Serial>>();
		adj->push_back(a);
	}
	Node(Serial i, Adjacencies a) : id{ i }, done{ false }, pre{ 0 }, post{ 0 } {
		adj = std::make_shared<std::vector<Serial>>();
	}

	void Clear() {
		done = false;
		pred = 0;
		pre = 0;
		post = 0;
	}

};

