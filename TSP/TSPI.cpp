#include "TSPI.h"


TSPI::TSPI(Graph G, int start) : g_{ G }, vertices_{}, route_{}/*, A_{}*/, allSets_{}, start_{ start }, distance_{ 0 }, vSize_{ static_cast<int>(G.d_.size()) }
{
	for (int v{ 0 }; v < vSize_; ++v) { vertices_.insert(v); }
	distance_ = solve(0);
}

TSPI::~TSPI()
{
}

int TSPI::distance()
{
	return static_cast<int>(distance_);
}

std::vector<int> TSPI::tour()
{
	std::vector<int> result;
	std::queue<int> route(route_);
	while (!route.empty()) {
		result.push_back(route.front());
		route.pop();
	}
	return result;
}

std::set<int> TSPI::allVertices()
{
	return std::set<int>(vertices_);
}

void TSPI::showSet(std::set<int> const & s) {
	std::copy(s.cbegin(), s.cend(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;
}

void TSPI::showSetVector(std::vector<std::set<int>> const & v) {
	for (auto const & s : v) {
		showSet(s);
	}
}

int TSPI::solve(int start)
{
	std::set<int> one{ 1 };
	int loop{ 0 };

	Memo lastA_;
	Memo thisA_;

	//A[{1},1] = 0   A[S,1] = inf
	for (int i{ 1 }; i < vSize_; ++i) {
		std::set<int> row{ i };
		std::map<int, int> baseRow;
		baseRow.emplace(0, INT_MAX);
		lastA_.emplace(row, baseRow);
	}
	std::set<int> source{ 0 };
	std::map<int, int> sourceRow;
	sourceRow.emplace(0, 0);
	lastA_.emplace(source, sourceRow);

	for (int s{ 1 }; s <= vSize_; ++s) {

		Combinations C;
		auto sets = C.readFile(s);

		//A[{1},1] = 0   A[S,1] = inf
		for (auto const & row : *(sets)) {
			std::map<int, int> baseRow;
			baseRow.emplace(0, INT_MAX);
			A_.emplace(row, baseRow);
		}
		std::set<int> source{ 0 };
		A_.at(source).at(0) = 0;

		for (auto const & S : *sets) {
			//std::cout << "Set " << ++loop << "\n";
			for (int j : S) {
				if (j == 0) { continue; }
				std::set<int> offset(S);
				offset.erase(j);
				int minVal{ INT_MAX };
				int curVal{ 0 };
				for (int k : S) {
					if (k == j) { continue; }
					int ckj{ g_.d_.at(k).at(j) };
					if (ckj == INT_MAX) {  // otherwise ckj will wrap
						curVal = INT_MAX;
					}
					else {
						int newVal{ A_.at(offset).at(k) };
						if (newVal == INT_MAX) {
							curVal = INT_MAX;
						}
						else {
							curVal = A_.at(offset).at(k) + ckj;
						}
					}
					if (curVal < minVal) { minVal = curVal; }
				}
				A_.at(S).emplace(j, minVal);
			}
		}

	}


	std::cout << "Starting distance calculation\n";
	int minVal{ INT_MAX };
	int curVal{ 0 };
	for (int j{ 1 }; j < vSize_; ++j) {
		int cj0{ g_.d_.at(j).at(0) };
		if (cj0 == INT_MAX) {  // otherwise ckj will wrap
			curVal = INT_MAX;
		}
		else {
			curVal = A_.at(vertices_).at(j) + cj0;
		}
		if (curVal < minVal) { minVal = curVal; }
	}
	return minVal;
}

int TSPI::calcAndSolve(int start)
{
	std::set<int> one{ 1 };
	int loop{ 0 };

	Memo lastA_;
	Memo thisA_;

	for (int s{ 1 }; s <= vSize_; ++s) {

		Combinations generator(vSize_, s);
		auto sets = generator.getSets();

		//A[{1},1] = 0   A[S,1] = inf
		for (auto const & row : *(sets)) {
			std::map<int, int> baseRow;
			baseRow.emplace(0, INT_MAX);
			thisA_.emplace(row, baseRow);
		}

		std::set<int> source{ 0 };
		std::map<int, int> sourceRow;
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
				int minVal{ INT_MAX };
				int curVal{ 0 };
				for (int k : S) {
					if (k == j) { continue; }
					int ckj{ g_.d_.at(k).at(j) };
					if (ckj == INT_MAX) {  // otherwise ckj will wrap
						curVal = INT_MAX;
					}
					else {
						int newVal{ lastA_.at(offset).at(k) };
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

	std::cout << "Starting distance calculation\n";
	int minVal{ INT_MAX };
	int curVal{ 0 };
	for (int j{ 1 }; j < vSize_; ++j) {
		int cj0{ g_.d_.at(j).at(0) };
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

void TSPI::printD(std::vector<std::vector<int>> & m)
{
	std::cout << "\t";
	for (int j{ 0 }; j < vSize_; ++j) {
		std::cout << std::setw(5) << static_cast<int>(j);
	}
	std::cout << std::endl;

	for (int j{ 0 }; j < vSize_; ++j) {
		std::cout << std::setw(4) << static_cast<int>(j) << "\t";
		for (int i{ 0 }; i < vSize_; ++i) {
			std::cout << std::setw(4) << static_cast<int>(m[j][i]) << " ";
		}
		std::cout << std::endl;
	}
}