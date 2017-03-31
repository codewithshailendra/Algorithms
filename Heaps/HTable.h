#pragma once
#include <memory>

struct node {
	size_t id;
	int value;
	std::shared_ptr<node> next;
	std::shared_ptr<node> last;

	node(size_t id_, int value_, std::shared_ptr<node> nxt, std::shared_ptr<node> lst) {
		id = id_; value = value_;
		next = nxt; last = lst;
	}
};



class HTable
{
public:

	HTable(size_t initialCapacity)	{
		focus = std::make_shared<node>(0,0,nullptr, nullptr);

		for (size_t i = 0; i < initialCapacity; ++i) {

		}
		
	}

	std::shared_ptr<node> insert(size_t id, int value) {
		focus->last = std::make_shared<node>(id, value, nullptr, focus);
		propably the wrong way around
	}

	~HTable()
	{
	}

private:
	std::shared_ptr<node> focus;
	

};

