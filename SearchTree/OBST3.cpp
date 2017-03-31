#include <iostream>

using namespace std;

int main()
{
	int n = 7;

	for (int s{ 0 }; s < n; ++s) {
		cout << "\ns = " << s << "\n";
		for (int i{ 1 }; i < n + 1; ++i) {
			cout << "i = " << i << "   A[" << i << ", " << i+s << "] is the minimum of:\n";
			for (int r{ i}; r < i + s + 1; ++r) {
				cout << " r= " << r << "\tA[i,r-1] = A[" << i << ", " << r - 1 << "]";
				if (i > r - 1) { cout << " = 0"; }
				cout << "\tA[r + 1, i + s] = A[" << r + 1 << ", " << i + s << "]";
				if (r + 1 > i + s) { cout << " = 0"; }
				cout << "\tSum p[" << i << "] to p[" << i + s << "]";
				cout << "\n";
			}
		}
	}
	
	
	
	return 0;
}

