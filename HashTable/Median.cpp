#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<algorithm>
#include <functional>
#include <queue>

using namespace std;
const string live{ R"(C:\Users\n419\Repos\HashTables\HashTables\Median.txt)" };
const string test{ R"(C:\Users\n419\Repos\HashTables\HashTables\extract.txt)" };

void getData(string name, std::vector<int> & v) {
	std::ifstream input(name);
	int value{ 0 };
	if (input.is_open()) {
		while (input >> value) {
			v.push_back(value);
		}
	}
	input.close();
}

int main()
{
	std::vector<int> data;
	getData(live, data);

	priority_queue<int, std::vector<int>, std::greater<int>> highHeap;
	priority_queue<int, std::vector<int>, std::less<int>> lowHeap;

	int msum{ 0 };

	auto it{ data.cbegin() };

	// make sure we have an entry in each heap to avoid an "if empty" condition in the main loop
	if (*it > *(it + 1)) {
		highHeap.push(*it);
		lowHeap.push(*(it + 1));
	}
	else {
		lowHeap.push(*it);
		highHeap.push(*(it + 1));
	}

	// don't forget to add the initial entries to the running sum
	msum = (msum + *it) % 10000;
	msum = (msum + lowHeap.top()) % 10000;

	it += 2;

	while (it != data.cend()) {
		if (*it > highHeap.top()) {
			highHeap.push(*it);
		}
		else {
			lowHeap.push(*it);
		}

		it++;

		if (highHeap.size() > lowHeap.size()) {
			lowHeap.push(highHeap.top());
			highHeap.pop();
		}  // HighHeap is never bigger than low heap
		else if (lowHeap.size() > highHeap.size() + 1) {
			highHeap.push(lowHeap.top());
			lowHeap.pop();
		} // lowheap size is never mode than one larger than highheap size

		// median is on the low heap for n = even (from questions definition) and on the 
		// largest heap for n = odd. However highheap can never be bigger than low heap so
		// the median is always on the lowHeap.

		msum = (msum + lowHeap.top()) % 10000;
	}

	std::cout << "Result = " << msum << std::endl;

	return 0;
}

