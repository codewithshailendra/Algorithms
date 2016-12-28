#pragma once
#include <vector>
#include <exception>
#include <cstdlib>

template<class ET>
class swapper {
	virtual void doSwap(std::vector<ET> & a, size_t l, size_t r) = 0;
};

template<class ET>
class MedianSwap: public swapper<ET> {
public:
	static void doSwap(std::vector<ET> & a, size_t l, size_t r) {
		size_t lastIndex = r - 1;
		size_t midIndex = l + ((lastIndex - l) / 2);
		size_t medianValue = median(a[l], a[midIndex], a[lastIndex]);
		if (medianValue == a[midIndex]) {
			std::swap(a[l], a[midIndex]);
		}
		else if (medianValue == a[lastIndex]) {
			std::swap(a[l], a[lastIndex]);
		}
		// else a[l] is already the median
	}

private:
	static inline int median(int a, int b, int c) {
		if ((a < b) && (a < c)) return std::min(b, c);
		if ((b < c) && (b < a)) return std::min(a, c);
		return std::min(a, b);
	}
};

template<class ET>
class RandomSwap: public swapper<ET> {
public:
	static void doSwap(std::vector<ET> & a, size_t l, size_t r) {
		size_t randomIndex{ l + (rand() % (r - l)) }; // random between 0 and (r-l)-1
		std::swap(a[l], a[randomIndex]);
	}
};


template <class T, class S>
class QSort
{

public:
	static void Sort(std::vector<T>& a) {
		qSort(a, 0, a.size());
	}

private:

	static size_t partitionM(std::vector<T> & a, size_t l, size_t r) {

		S::doSwap(a, l, r);

		T p{ a[l] };

		size_t i{ l + 1 };
		size_t j{ i };

		while (j < r) {
			if (a[j] < p) {
				std::swap(a[i++], a[j]);
			}
			++j;
		}
		std::swap(a[--i], a[l]);
		return i;
	}

	static void qSort(std::vector<T> & a, size_t l, size_t r) {
		if (r <= l) return;
		size_t partitionIndex{ partitionM(a,l,r) };
		qSort(a, l, partitionIndex);
		qSort(a, partitionIndex + 1, r);
	}

};
