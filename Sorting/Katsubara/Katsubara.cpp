#include<iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <ios>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;
using big = long double;

string ss1{ R"(3141592653589793238462643383279502884197169399375105820974944592)" };
string ss2{ R"(2718281828459045235360287471352662497757247093699959574966967627)" };
string s1{ R"(1234)" };
string s2{ R"(4321)" };

/*

function multiply(x; y)
Input: Positive integers x and y, in binary
Output: Their product
n = max(size of x, size of y)
if n = 1: return xy
xL, xR = leftmost dn=2e, rightmost bn=2c bits of x
yL, yR = leftmost dn=2e, rightmost bn=2c bits of y
P1 = multiply(xL; yL)
P2 = multiply(xR; yR)

P3 = multiply(xL + xR; yL + yR)

return P1 * 2^n + (P3 - P1 - P2)  2^(n/2) + P2

*/

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
	string s{ ss.str() };
	size_t half{ s.length() };
	half = half / 2 + (half % 2);
	string aString(s.substr(0, half));
	string bString(s.substr(half));
	cout << fixed << setprecision(0);
	//cout << s << " => " << aString << " & " << bString << endl;
	ss.clear();
	ss.str(aString);
	ss >> a;
	ss.clear();
	ss.str(bString);
	ss >> b;
	cout << fixed << setprecision(0);
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
	if (digitsIn(n1) == 1 && digitsIn(n2) == 1) {
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
	if (digitsIn(n1) == 1 && digitsIn(n2) == 1) {
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

long long K(vector<int> x, vector<int> y, int n) {

	if (n == 1) {
		cout << "-> " << x[0] << " & " << y[0] << "\n";
		return x[0] * y[0];
	}
	int l = n / 2;
	vector<int> a(l, 0);
	vector<int> b(l, 0);
	vector<int> c(l, 0);
	vector<int> d(l, 0);

	for (int i{ 0 }; i < l; ++i) {
		a[i] = x[i];
		b[i] = x[i + l];
		c[i] = y[i];
		d[i] = y[i + l];
	}

	long long U = K(a, c, l);
	long long V = K(a, d, l);
	long long W = K(b, c, l);
	long long X = K(b, d, l);
	long long result = (U * tenToTheN(n)) + (tenToTheN(l) * (V + W)) + X;
	cout << result << "\n";
	return result;
}

int main()
{
	vector<int> X(s1.size(), 0);
	vector<int> Y(s2.size(), 0);

	for (int i{ 0 }; i < s1.size(); ++i) {
		string a{ s1[i] };
		X[i] = atoi(a.c_str());
		string b{ s2[i] };
		Y[i] = atoi(b.c_str());
	}

	cout << K(X, Y, s1.size());

	return 0;
}

