#include "targetver.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<int> a{ 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };
	size_t n{ a.size()};
	vector<int> s(n+1, 0);

	for (size_t j{ 1 }; j < n; ++j) {
		cout << "j=" << j << "\n";
		int max{ INT_MIN };
		for (size_t i{ 0 }; i < j; ++i) {
			cout << "\t i=" << i << "\n";
			int sum{ 0 };
			for (size_t k{ 0 }; k <= i; ++k) {
				cout << "j-k=" << j - k << " : ";
				sum = +a[j - k];
			}
			cout << "sum=" << sum << ", ";
			if (sum > max) { max = sum; }
			cout << std::endl;
		}
		int result{ (max > s[j - 1]) ? max : s[j - 1] };
		s[j] = result;
		cout << "\n";
	}
	std::cout << "\nResults\n";

	for (auto const i : s) {
		std::cout << i << ", ";
	}
	cout << "\n";
	return 0;
}

