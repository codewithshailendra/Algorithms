// A naive recursive implementation of optimal binary search tree problem
#include <stdio.h>
#include <limits.h>
#include <iostream>

// A utility function to get sum of array elements freq[i] to freq[j]
int sum(int freq[], int i, int j);

// A recursive function to calculate cost of optimal binary search tree
int optCost(int freq[], int i, int j)
{
	// Base cases
	if (j < i)	 // If there are no elements in this subarray
		return 0;
	if (j == i)	 // If there is one element in this subarray
		return freq[i];

	// Get sum of freq[i], freq[i+1], ... freq[j]
	int fsum = sum(freq, i, j);

	// Initialize minimum value
	int min = INT_MAX;

	// One by one consider all elements as root and recursively find cost
	// of the BST, compare the cost with min and update min if needed
	for (int r = i; r <= j; ++r)
	{
		int cost = optCost(freq, i, r - 1) + optCost(freq, r + 1, j);
		if (cost < min)
			min = cost;
	}

	// Return minimum value
	return min + fsum;
}

// The main function that calculates minimum cost of a Binary Search Tree.
// It mainly uses optCost() to find the optimal cost.
int optimalSearchTree(int keys[], int freq[], int n)
{
	// Here array keys[] is assumed to be sorted in increasing order.
	// If keys[] is not sorted, then add code to sort keys, and rearrange
	// freq[] accordingly.
	return optCost(freq, 0, n - 1);
}

// A utility function to get sum of array elements freq[i] to freq[j]
int sum(int freq[], int i, int j)
{
	int s = 0;
	for (int k = i; k <= j; k++)
		s += freq[k];
	return s;
}

// Driver program to test above functions
int main()
{
	int keys[] = { 1,2,3,4,5,6,7 };
	int freq[] = { 20,5,17,10,20,3,25 };
	int n = sizeof(keys) / sizeof(keys[0]);
	printf("Cost of Optimal BST is %d ", optimalSearchTree(keys, freq, n));
	

	n = 7;

	for (int s{ 0 }; s < n; ++s) {
		std::cout << "\ns = " << s << "\n";
		for (int i{ 1 }; i < n + 1; ++i) {
			std::cout << "i = " << i << "   A[" << i << ", " << i + s << "] is the minimum of:\n";
			for (int r{ i }; r < i + s + 1; ++r) {
				std::cout << " r= " << r << "\tA[i,r-1] = A[" << i << ", " << r - 1 << "]";
				if (i > r - 1) { std::cout << " = 0"; }
				std::cout << "\tA[r + 1, i + s] = A[" << r + 1 << ", " << i + s << "]";
				if (r + 1 > i + s) { std::cout << " = 0"; }
				std::cout << "\tSum p[" << i << "] to p[" << i + s << "]";
				std::cout << "\n";
			}
		}
	}

}
