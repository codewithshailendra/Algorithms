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
