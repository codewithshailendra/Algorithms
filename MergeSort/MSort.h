#pragma once
#include <vector>

using std::vector;

template <typename T>
class MSort
{
public:
	MSort<T>();
	vector<T> sort( vector<T> const & a);

private:
	vector<T> mrg(vector<T> const & a, vector<T> const & b);
	vector<T> msort(vector<T> const & a);
};


template<typename T>
MSort<T>::MSort()
{
}

template <typename T>
vector<T> MSort<T>::sort(vector<T> const & a)
{
	return msort(a);
}

template <typename T>
vector<T> MSort<T>::mrg(vector<T> const & a, vector<T> const & b) {
	size_t n{ a.size() };
	size_t n2{ n << 1 };
	vector<T> result(n2);
	size_t ia{ 0 };
	size_t ib{ 0 };
	size_t i{ 0 };
	while (i < n2 && ia < n && ib < n) {
		if (a[ia] < b[ib]) {
			result[i++] = a[ia++];
		}
		else {
			result[i++] = b[ib++];
		}
	}
	if (ia < n) while (ia < n) result[i++] = a[ia++];
	if (ib < n) while (ib < n) result[i++] = b[ib++];
	return result;
}

template <typename T>
vector<T> MSort<T>::msort(vector<T> const & a) {
	size_t n{ a.size() };
	size_t n2{ n >> 1 };
	if (n < 2) return a;
	vector<T> l(a.cbegin(), a.cbegin() + n2);
	vector<T> r(a.cbegin() + n2, a.cend());
	l = msort(l);
	r = msort(r);
	return mrg(l, r);
}