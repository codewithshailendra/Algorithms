#include "QSort.h"
#include <iterator>
#include <algorithm>
#include <iostream>
int main()
{
	std::vector<int> A{ 6,8,7,3,4,2,5,1 };
	
	std::copy(A.cbegin(), A.cend(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;
	QSort<int>::Sort(A);
	std::copy(A.cbegin(), A.cend(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;
	
	return 0;
}

