#include <vector>
#include <bitset>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>

using triple = std::bitset<3>;

struct bits {
	std::bitset<3> digits;

	bits(std::string stg) {
		digits = std::bitset<3>(stg);
	}
	int to_value() {
		return digits.to_ulong();
	}
};

std::ostream & operator<<(std::ostream & os, bits b) {
	std::cout << b.digits << " [" << b.to_value() << "]";
	return os;
}

std::ostream & operator<<(std::ostream & os, std::vector<bits> const & vb) {
	std::copy(vb.cbegin(), vb.cend(), std::ostream_iterator<bits>(os, "\n"));
	return os;
}

std::ostream & operator<<(std::ostream & os, triple b) {
	std::cout << b.to_string() << " [" << b.to_ullong() << "]";
	return os;
}

bool operator<(triple const & lhs, triple const & rhs) {
	return lhs.to_ullong() < rhs.to_ullong();
}

std::ostream & operator<<(std::ostream & os, std::map<int, int> const & m) {
	for (auto const & element : m) {
		std::cout << element.first << " : " << element.second << "\n";
	}
	return os;
}

int hamming_distance(unsigned x, unsigned y)
{
	int dist = 0;
	unsigned  val = x ^ y;

	// Count the number of bits set
	while (val != 0)
	{
		// A bit is set, so increment the count and clear the bit
		dist++;
		val &= val - 1;
	}

	// Return the number of differing bits
	return dist;
}

void showDistance(std::vector<std::bitset<24>> const & v) {
	size_t l{ v.size() };
	for (size_t i{ 0 }; i < l; ++i) {
		std::bitset<24> current{ v[i] };
		for (size_t j{ i + 1 }; j < l; ++j) {
			std::bitset<24> xor{ current^v[j] };
			size_t hamming{ xor.count() };
			std::cout << "Distance from " << i << " [" << current << "] to " << j << " [" << v[j] << "] is " << hamming << "\n";
			current = v[j];
		}
	}
}

bool near(std::bitset<24> const & u, std::bitset<24> const & v) {
	return ((u^v).count() < 3);
}

int scan(std::vector<std::bitset<24>> const & v) {
	size_t l{ v.size() };
	int nearNodes{ 0 };
	for (size_t i{ 0 }; i < l; ++i) {
		std::bitset<24> current{ v[i] };
		for (size_t j{ i + 1 }; j < l; ++j) {
			if (near(current, v[j])) {
				nearNodes++;
				std::cout << current << " and " << v[j] << std::endl;
			}
			current = v[j];
		}
	}
	return nearNodes;
}

int main()
{
	std::vector<std::bitset<3>> v;
	v.emplace_back("000");
	v.emplace_back("001");
	v.emplace_back("010");
	v.emplace_back("011");
	v.emplace_back("100");
	v.emplace_back("101");
	v.emplace_back("110");
	v.emplace_back("111");


	size_t l{ v.size() };
	for (size_t i{ 0 }; i < l; ++i) {
		triple current{ v[i] };
		for (size_t j{ i + 1 }; j < l; ++j) {
			triple xor{ current^v[j] };
			size_t hamming{ xor.count() };
			std::cout << "Distance from " << i << " [" << current << "] to " << j << " [" << v[j] << "] is " << hamming << "\n";
			current = v[j];
		}
	}



	return 0;
}

