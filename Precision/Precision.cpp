#include<iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <ios>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

using namespace std;
using vec = vector<int>;
constexpr unsigned z = '0';

string ss1{ R"(3141592653589793238462643383279502884197169399375105820974944592)" };
string ss2{ R"(2718281828459045235360287471352662497757247093699959574966967627)" };
string s1{ R"(012345678123456781234567812345678)" };
string s2{ R"(012345678123456781234567812345678)" };
string t1{ R"(23456)" };
string t2{ R"(61)" };

template <typename T>
void show(vector<T> v) {
	copy(v.crbegin(), v.crend(), ostream_iterator<T>(cout));
	cout << endl;
}

vec vectorize(string s) {
	vec result(s.length(), 0);
	size_t i{ 0 };
	for_each(s.crbegin(), s.crend(), [&result, &i](char c) {result[i++] = static_cast<unsigned>(c) - z; });
	return result;
}

vec add(vec a, vec b) {
	size_t minLen{ min(a.size(),b.size()) };
	size_t maxLen{ max(a.size(),b.size()) };
	vec result(maxLen + 1, 0);
	size_t i{ 0 };

	while (i < minLen) {
		auto res = div(a[i] + b[i], 10);
		auto carry = div(result[i]+res.rem,10);
		result[i] = carry.rem;
		result[i + 1] = res.quot + carry.quot;
		++i;
	}
	while (i < a.size()) {
		result[i] += a[i];
		++i;
	}
	while (i < b.size()) {
		result[i] += b[i];
		++i;
	}
	// remove leading zeros
	if (result.back() == 0) { result.pop_back(); }
	show(result);
	return result;
}

void accumulate(vec & a, vec b) {
	size_t minLen{ min(a.size(),b.size()) };
	size_t maxLen{ max(a.size(),b.size()) };
	vec result(maxLen + 1, 0);
	size_t i{ 0 };

	while (i < minLen) {
		auto res = div(a[i] + b[i], 10);
		auto carry = div(result[i] + res.rem, 10);
		result[i] = carry.rem;
		result[i + 1] = res.quot + carry.quot;
		++i;
	}
	while (i < a.size()) {
		result[i] += a[i];
		++i;
	}
	while (i < b.size()) {
		result[i] += b[i];
		++i;
	}
	// remove leading zeros
	if (result.back() == 0) { result.pop_back(); }	
	// put the result back in a
	a.clear();
	for (auto const & e : result) {
		a.push_back(e);
	}

}

vec mult(vec v, int m, unsigned p) {
	size_t resLen{ v.size() + p + 1 };
	vec result(resLen, 0);
	size_t i{ p };
	for (auto const & e : v) {
		auto res = div(e * m, 10);
		auto carry = div(result[i] + res.rem, 10);
		result[i] = carry.rem;
		result[i + 1] = res.quot + carry.quot;
		++i;
	}
	if (result.back() == 0) { result.pop_back(); }
	return result;
}

vec multiplier(const vec & a, const vec & b) {
	assert(!(b.size() > a.size()));
	vec result;
	vector<vec> rows;
	size_t i{ 0 };
	for (size_t i{ 0 }; i < b.size(); ++i) {
		rows.push_back(mult(a, b[i], i));
	}

	for (auto const & row : rows) {
		accumulate(result, row);
	}
	return result;
}

vec multiply(const vec & a, const vec & b) {
	if (a.size() > b.size()) {
		return multiplier(a, b);
	}
	else {
		return multiplier(b, a);
	}
}

int main()
{
	vec v1{ vectorize(ss1) };
	vec v2{ vectorize(ss2) };
	show(multiply(v1, v2));

	string result{ R"(8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184)" };

	return 0;
}

