#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>
#include <exception>
#include "Heap2.h"

int main()
{
	Heap h(16);
	h.initialise();
	h.show();
	for (int i = 0; i < 150; ++i) {
		int v;
		std::cin >> v;
		if (v == 0) {
			std::cout << "\nmin is " << h.pop() << std::endl;
		}
		else
		{
			h.insert(v);
		}
		h.show();
	}
	return 0;
}

