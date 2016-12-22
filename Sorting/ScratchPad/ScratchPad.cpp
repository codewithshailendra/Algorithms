#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int median(int a, int b, int c) {
	if ((a < b) && (a < c)) return min(b, c);
	if ((b < c) && (b < a)) return min(a, c);
	return min(a, b);
}

int main()
{
	while (true) {
		int a, b, c;
		cin >> a >> b >> c;
		cout << "\nMedian of " << a << ", " << b << " and " << c << " is " << median(a, b, c) << endl;
	}

	return 0;
}

