#pragma once
#include <ratio>
#include <chrono>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
using std::chrono::system_clock;
using std::chrono::time_point;
using std::chrono::milliseconds;
typedef typename std::chrono::system_clock clockType;
typedef typename clockType::time_point tpType;

class Stopwatch
{
public:
	Stopwatch(int i = 0);
	void start(int i = 0);
	void stop(int i = 0);
	void reset(int i = 0);
	long long elapsed(int i = 0);
	std::string display(int i = 0);
	~Stopwatch();

private:
	clockType clock;
	std::map<int, tpType> starts;
	std::map<int, tpType> stops;
};




