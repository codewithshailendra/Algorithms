#include "TSP.h"


TSP::TSP(Graph2 G, int start) : g_{ G }, vertices_{}, start_{ start }, distance_{ 0 }, vSize_{ static_cast<int>(G.d_.size()) }
{
	for (int v{ 0 }; v < vSize_; ++v) { vertices_.insert(v); }
	distance_ = solve(0);
}

int TSP::distance()
{
	return static_cast<int>(distance_);
}

double TSP::solve(int start)
{
	std::set<int> one{ 1 };
	int loop{ 0 };

	Memo lastA_;
	Memo thisA_;

	//A[{1},1] = 0   A[S,1] = inf
	for (int i{ 1 }; i < vSize_; ++i) {
		std::set<int> row{ i };
		std::map<int, double> baseRow;
		baseRow.emplace(0, INT_MAX);
		lastA_.emplace(row, baseRow);
	}
	std::set<int> source{ 0 };
	std::map<int, double> sourceRow;
	sourceRow.emplace(0, 0);
	lastA_.emplace(source, sourceRow);

	for (int s{ 1 }; s <= vSize_; ++s) {

		Combinations generator;
		// Combinations for a 25 city problem are pre-calculated
		auto sets = generator.readFile(s);

		//A[{1},1] = 0   A[S,1] = inf
		for (auto const & row : *(sets)) {
			std::map<int, double> baseRow;
			baseRow.emplace(0, INT_MAX);
			thisA_.emplace(row, baseRow);
		}

		std::set<int> source{ 0 };
		std::map<int, double> sourceRow;
		sourceRow.emplace(0, 0);
		if (thisA_.count(source) == 0) {
			thisA_.emplace(source, sourceRow);
		}
		else
		{
			thisA_.at(source).at(0) = 0;
		}

		for (auto const & S : *sets) {
			for (int j : S) {
				if (j == 0) { continue; }
				std::set<int> offset(S);
				offset.erase(j);
				double minVal{ INT_MAX };
				double curVal{ 0 };
				for (int k : S) {
					if (k == j) { continue; }
					double ckj{ g_.d_.at(k).at(j) };
					if (ckj == INT_MAX) {  // otherwise ckj will wrap
						curVal = INT_MAX;
					}
					else {
						double newVal{ lastA_.at(offset).at(k) };
						if (newVal == INT_MAX) {
							curVal = INT_MAX;
						}
						else {
							curVal = newVal + ckj;
						}
					}
					if (curVal < minVal) { minVal = curVal; }
				}
				thisA_.at(S).emplace(j, minVal);
			}
		}
		lastA_.swap(thisA_);
		thisA_.clear();
	}

	double minVal{ INT_MAX };
	double curVal{ 0 };
	for (int j{ 1 }; j < vSize_; ++j) {
		double cj0{ g_.d_.at(j).at(0) };
		if (cj0 == INT_MAX) {  // otherwise ckj will wrap
			curVal = INT_MAX;
		}
		else {
			curVal = lastA_.at(vertices_).at(j) + cj0;
		}
		if (curVal < minVal) { minVal = curVal; }
	}
	return minVal;
}

