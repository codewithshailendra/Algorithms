#include "CombGen.h"

std::vector<std::set<int>> CombGen::Combinations(int n, int k)
{
	auto c = std::make_shared<std::vector<int>>(n);
	for (int i{ 0 }; i < k; ++i) {c->at(i)=i;}

	std::cout << "k = " << k << std::endl;

	do 
	{
	std::copy(c->cbegin(), c-> cend(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;
	} while (nextComb(c, k, n) == 1);
	
	return std::vector<std::set<int>>();
}

int CombGen::nextComb(std::shared_ptr<std::vector<int>> & comb, int n, int k) {
	int i = k - 1;
	comb->at(i) += 1;
	while ((i > 0) && (comb->at(i) >= n - k + 1 + i)) {
		--i;
		comb->at(i) += 1;
	}
	if (comb->at(0) > n - k) { return 0; }
	for (i = i + 1; i < k; ++i) {
		comb->at(i) = comb->at(i - 1) + 1;
	}
	return 1;
}
