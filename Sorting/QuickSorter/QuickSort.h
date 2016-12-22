#pragma once
#include <vector>
#include <algorithm>
#include <random>

class QuickSort
{
public:
	QuickSort() : dre_{}, comparisons_{0}, compCheck_{ 0 } {};
	void sort(std::vector<int>& A) { 
		comparisons_ = 0;
		compCheck_ = 0;
		qSort(A, 0, A.size()); 
		if (comparisons_ == compCheck_) std::cout << "Completed with " << comparisons_ << " comparisons" << std::endl;
		else std::cout << comparisons_ << " != " << compCheck_ << std::endl;
	};
	long long getComparisons() { return comparisons_; };
private:
	std:: default_random_engine dre_;
	long long comparisons_;
	long long compCheck_;
	void swap(int& a, int& b) {
		int temp{ b };
		b = a;
		a = temp;
	}

	// return a random integer in half open set lo, hi
	int getRandom(int lo, int hi) {
		std::uniform_int_distribution<int> uid(lo, hi - 1);
		int result{ uid(dre_) };
		return result;
	}

	int partition(std::vector<int> & a, int l, int r) {
		//swap(a[l], a[getRandom(l, r)]);
		int p = a[l];
		int i = l + 1;
		
		for (int j = l + 1; j < r; ++j) {
			compCheck_+=1;
			if (a[j] < p) {
				swap(a[i], a[j]);
				i++;
			}
		}
		swap(a[l], a[i-1]);
		return i;
	}

	void qSort(std::vector<int>& a, int l, int r) {
		if (r <= l) return;
		comparisons_ += r - l - 1;
		int pIndex;
		pIndex = partition(a, l, r);
		qSort(a, l, pIndex-1);
		qSort(a, pIndex, r);
	}
};

