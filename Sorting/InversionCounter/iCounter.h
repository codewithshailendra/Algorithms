#pragma once
#include <vector>
#include <iterator>
#include <algorithm>

using std::vector;

template <class T>
class iCounter
{
public:
	iCounter(vector<T> a) : inversions_{ 0 }, a_{ a.cbegin(), a.cend() } {};
	int inversions() { inversions_ = 0;  msort(a_); return inversions_; };
	int brut() {
		inversions_ = 0;
		for (size_t i = 0; i < a_.size(); ++i) {
			for (size_t j = i; j < a_.size(); ++j) {
				if (a_[i] > a_[j]) {
					inversions_++;
				}
			}
		}
		return inversions_;
	};

private:
	int inversions_;
	const vector<T> a_;
	void show() {
		copy(a_.cbegin(), a_.cend(), ostream_iterator<T>(cout, " "));
	};

	template <typename T>
	vector<T> mrg(vector<T> const & a, vector<T> const & b) {
		size_t n{ a.size() };
		size_t n2{ n << 1 };
		vector<T> result(n2);
		size_t ia{ 0 };
		size_t ib{ 0 };
		size_t i{ 0 };
		while (i < n2 && ia < n && ib < n) {
			if (a[ia] > b[ib]) {
				inversions_ += n - ia;
				result[i++] = b[ib++];	
			}
			else {
				result[i++] = a[ia++];
			}
		}
		if (ia < n) while (ia < n) {
			result[i++] = a[ia++];
		}
		if (ib < n) while (ib < n) {
			result[i++] = b[ib++];
		}
		return result;
	}

	template <typename T>
	vector<T> msort(vector<T> const & a) {
		size_t n{ a.size() };
		size_t n2{ n >> 1 };
		if (n < 2) return a;
		vector<T> l(a.cbegin(), a.cbegin() + n2);
		vector<T> r(a.cbegin() + n2, a.cend());
		l = msort(l);
		r = msort(r);
		return mrg(l, r);
	}
};



