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
string s1{ R"(12345678123456781234567812345678)" };
string s2{ R"(12345678123456781234567812345678)" };

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

big K(vector<int> x, vector<int> y, int n) {

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

	big U = K(a, c, l);
	big V = K(a, d, l);
	big W = K(b, c, l);
	big X = K(b, d, l);
	big result = (U * tenToTheN(n)) + (tenToTheN(l) * (V + W)) + X;
	cout << result << "\n";
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

	return 0;
}

