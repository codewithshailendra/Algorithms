#include<iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <ios>
#include <iomanip>

using namespace std;

string ss1{ R"(3141592653589793238462643383279502884197169399375105820974944592)" };
string ss2{ R"(2718281828459045235360287471352662497757247093699959574966967627)" };
string s1{ R"(12345)" };
string s2{ R"(56778)" };

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

unsigned long long power(unsigned x) {
	int p{ 1 };
	while (x--) p *= 10;
	return p;
}

unsigned long long Karatsuba(string s1, string s2 ) {
	if (s1.length() == 1 && s2.length() == 1) {  
		long A{ atol(s1.c_str()) };
		long B{ atol(s2.c_str()) };
		long result = A*B;
		return result;
	}

	//cout << s1 << " x " << s2 << "\n";
	auto n11{ s1.length() };
	auto n12{ n11 /2 };
	auto n21{ s2.length() };
	auto n22{ n21 /2 };
	if (n11 > n12) {
		string newstring(n11-n21,'0');
		s2 = newstring + s2;
		cout << s2 << "\n";
	}
	else if (n12 > n11) {
		string newstring(n21 - n11, '0');
		s1 = newstring + s1;
		cout << s2 << "\n";
	}
	string high1{ s1.substr(0, n12) };
	string low1{ s1.substr(n12,n12) };
	string high2{ s2.substr(0,n22) };
	string low2{ s2.substr(n22,n22) };
	unsigned long long result1 = power(n11) * Karatsuba(high1, high2);
	unsigned long long result2 = (power(n12)*((Karatsuba(high1, low2) + Karatsuba(low1, high2))));
	unsigned long long result3 = Karatsuba(low1, low2);
	if (result1 > LONG_MAX) cout << "Overflow risk on result 1\n";
	if (result2 > LONG_MAX) cout << "Overflow risk on result 2\n";
	if (result3 > LONG_MAX) cout << "Overflow risk on result 3\n";
	cout << fixed << setprecision(0);
	unsigned long long result = result1 + result2 + result3; 
	cout << "Result = " << result << "\n";
	return result;
}

int main()
{

	auto k = Karatsuba(s1, s2);

	stringstream ss1{ s1 };
	stringstream ss2{ s2 };
	unsigned long long x1;
	unsigned long long x2;
	ss1 >> x1;
	ss2 >> x2;
	unsigned long long result{ x1 * x2 };
	cout << fixed << setprecision(0); 
	cout << " Check = " << result << endl;
	if (result != k) cout << "Error\n";
	return 0;
}

