#pragma once
#include <vector>
#include <exception>
#include <cstdlib>


// return the nth order statistic in linear time
template <class T>
class Selector
{
public:
	static T nthOrder(std::vector<T> & a, size_t nth) {
		return select(a, 0, a.size(),nth);
	}

private:

	static size_t partitionM(std::vector<T> & a, size_t l, size_t r) {
		if (r == l) return l;
		std::swap(a[l], a[l + (rand() % (r - l))]);
		T p{ a[l] };
		size_t i{ l + 1 };
		size_t j{ i };
		while (j < r) {
			if (a[j] < p) {std::swap(a[i++], a[j]);}
			++j;
		}
		std::swap(a[--i], a[l]);
		return i;
	}

	static T select(std::vector<T> & a, size_t l, size_t r, size_t nth) {
		size_t partitionIndex{ partitionM(a,l,r) };
		if (nth < partitionIndex) {  // then recurse in the lower division
			return select(a, l, partitionIndex, nth);
		}
		else if (nth > partitionIndex) {  //then recurse in the upper division
			return select(a, partitionIndex+1, r, nth);
		}
		else { // we have found the nth order statistic
			return a[partitionIndex];
		}
		return 0;
	}
};

