#pragma once

struct Jenkins
{
	static unsigned int Hash(long long val) {
		return std::abs(val) % 1000000;
	}
};

struct Mod
{
	static unsigned int Hash(long long val) {
		return std::abs(val) % 1000000;
	}
};