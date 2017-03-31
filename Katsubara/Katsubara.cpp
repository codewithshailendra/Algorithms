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
using big = long long;
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

vec scale(vec v, int m, unsigned p) {
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
		rows.push_back(scale(a, b[i], i));
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

unsigned power(unsigned x) {
	int p{ 1 };
	while (x--) p *= 10;
	return p;
}

// splits the charcters of number into two 
void splitter(big number, big & a, big & b) {
	a = 0; b = 0;
	stringstream ss;
	ss << number;
	string s;
	ss >> fixed >> setprecision(0) >> s;
	size_t half{ s.length() };
	half = half / 2 + (half % 2);
	string aString(s.substr(0, half));
	string bString(s.substr(half));
	//cout << fixed << setprecision(0);
	//cout << s << " => " << aString << " & " << bString << endl;
	ss.clear();
	ss.str(aString);
	ss >> fixed >> setprecision(0) >> a;
	ss.clear();
	ss.str(bString);
	ss >> b;
	//cout << fixed << setprecision(0);
	//cout << number << " => " << a << " & " << b << endl;
}

big tenToTheN(big number) {
	stringstream ss;
	ss << number;
	string s{ ss.str() };
	return power(s.length());
}

big tenToTheN2(big number) {
	stringstream ss;
	ss << number;
	string s{ ss.str() };
	unsigned len{ s.length() };
	len = len / 2 + (len % 2);
	return power(s.length() >> 1);
}

big digitsIn(big number) {
	stringstream ss;
	ss << number;
	string s{ ss.str() };
	return s.length();
}

big Karatsuba(big n1, big n2) {
	if (n1 > 9 && n2 > 9) {
		return n1 * n2;
	}

	big tenN{ tenToTheN(n1) };
	big ten2n{ tenToTheN2(n1) };
	big a, b, c, d;
	splitter(n1, a, b);
	splitter(n2, c, d);
	big ac{ Karatsuba(a,c) };
	big bd{ Karatsuba(b,d) };
	big ad{ Karatsuba(a,d) };
	big bc{ Karatsuba(b,c) };
	return (tenN * ac) + (ten2n * (ad + bc)) + bd;
}

big Karatsuba2(big n1, big n2) {
	if (n1 > 9 && n2 > 9) {
		return n1 * n2;
	}

	big tenN{ tenToTheN(n1) };
	big ten2n{ tenToTheN2(n1) };
	big a, b, c, d;
	splitter(n1, a, b);
	splitter(n2, c, d);
	big z1{ Karatsuba2(a,c) };
	big z2{ Karatsuba2(b,d) };
	big z3{ Karatsuba2(a + b, c + d) };
	big z4{ z3 - z1 - z2 };
	return (tenN * z1) + (ten2n * z4) + z2;
}

vector<int> K(vector<int> x, vector<int> y) {
	// Note - digits need to be reversed in the vector
	int n = x.size();
	if (x.size() == 1 && y.size() == 1) {
		cout << "-> " << x[0] << " & " << y[0] << "\n";
		return vector<int>(1, x[0] * y[0]);
	}
	int l = n / 2;
	vector<int> a(l, 0);
	vector<int> b(l, 0);
	vector<int> c(l, 0);
	vector<int> d(l, 0);

	for (int i{ 0 }; i < l; ++i) {
		b[i] = x[i];
		a[i] = x[i + l];
		d[i] = y[i];
		c[i] = y[i + l];
	}

	vector<int> U = K(a, c);
	vector<int> V = K(a, d);
	vector<int> W = K(b, c);
	vector<int> X = K(b, d);
	vector<int> VW{ add(V,W) };
	vector<int> VWP2{ scale(VW,1,tenToTheN(l)) };
	vector<int> UP2{ scale(U,1,tenToTheN(n)) };
	vector<int> result{ add(UP2,VWP2) };
	accumulate(result, X);
	return result;
}

int main()
{
	cout << fixed << setprecision(0);
	//cout << "Max value long long is " << LDBL_MAX << endl;
	big A;
	big B;
	stringstream ssa{ s1 };
	ssa << fixed << setprecision(0);
	ssa >> A;
	stringstream ssb{ s1 };
	ssb << fixed << setprecision(0);
	ssb >> B;
	cout << fixed << setprecision(0);
	cout << A << endl;
	cout << Karatsuba(A, B) << endl;
	cout << Karatsuba2(A, B) << endl;
	cout << A * B << endl;
	show(K(vectorize(t1), vectorize(t2)));
	return 0;
}

