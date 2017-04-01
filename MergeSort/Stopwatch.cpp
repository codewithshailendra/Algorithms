#include "Stopwatch.h"

Stopwatch::Stopwatch(int i)
{
	cout << "Stopwatch tick = " << 1000000.0 / clockType::period().den << " milliseconds" << endl;
}

void Stopwatch::start(int i)
{
	starts[i] = clock.now();
}

void Stopwatch::stop(int i)
{
	stops[i] = clock.now();
}

long long Stopwatch::elapsed(int i)
{
	return std::chrono::duration_cast<std::chrono::microseconds>(stops.at(i) - starts.at(i)).count();
}

std::string Stopwatch::display(int i) {
	std::stringstream ss;
	auto dur{ stops.at(i) - starts.at(i) };
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
	auto mcs = std::chrono::duration_cast<std::chrono::microseconds>(dur);
	auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur);
	ss << ms.count() << " milliseconds   " << mcs.count() << " microseconds   "; // << dur.count() << " ticks   " << ns.count() << " nanoseconds";
	return ss.str();
}

void Stopwatch::reset(int i)
{
	starts.erase(i);
	stops.erase(i);
}

Stopwatch::~Stopwatch()
{
}
