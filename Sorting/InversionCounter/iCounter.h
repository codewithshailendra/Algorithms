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
	long long inversions() { inversions_ = 0;  msort(a_); return inversions_; };
	long long brut() {
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
	long long inversions_;
	const vector<T> a_;
	void show() {
		copy(a_.cbegin(), a_.cend(), ostream_iterator<T>(cout, " "));
	};

	template <typename T>
	vector<T> mrg(vector<T> const & a, vector<T> const & b) {
		// lengths will be different for n != 2^m
		size_t an{ a.size() };
		size_t bn{ b.size() };
		size_t n2{ an + bn };
		vector<T> result(n2);
		size_t ia{ 0 };
		size_t ib{ 0 };
		size_t i{ 0 };
		while (i < n2 && ia < an && ib < bn) {
			if (a[ia] > b[ib]) {
				inversions_ += an - ia;
				result[i++] = b[ib++];
			}
			else {
				result[i++] = a[ia++];
			}
		}
		while (ia < an) {
			result[i++] = a[ia++];
		}
		while (ib < bn) {
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
		//cout << inversions_ << "\n";
		return mrg(l, r);
	}
};



