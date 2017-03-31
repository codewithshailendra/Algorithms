#include "Graph.h"

Graph::Graph() : x_{}, y_{}, d_{ std::vector<std::vector<int>>(4,std::vector<int>(4)) }, v_{ 4 }
{
	//d_[1][1] = 0;  d_[1][2] = 2; d_[1][3] = 9;  d_[1][4] = 10;
	//d_[2][1] = 1;  d_[2][2] = 0; d_[2][3] = 6;  d_[2][4] = 4;
	//d_[3][1] = 15; d_[3][2] = 7; d_[3][3] = 0;  d_[3][4] = 8;
	//d_[4][1] = 6;  d_[4][2] = 3; d_[4][3] = 12; d_[4][4] = 0;

	d_[0][0] = 0;  d_[0][1] = 2; d_[0][2] = 9;  d_[0][3] = 10;
	d_[1][0] = 1;  d_[1][1] = 0; d_[1][2] = 6;  d_[1][3] = 4;
	d_[2][0] = 15; d_[2][1] = 7; d_[2][2] = 0;  d_[2][3] = 8;
	d_[3][0] = 6;  d_[3][1] = 3; d_[3][2] = 12; d_[3][3] = 0;
}

Graph::Graph(std::string fname) : x_{}, y_{}, d_{}, v_{ 0 }
{
	getData(fname);
	setDistances();
}

Graph::~Graph()
{
}


void Graph::getData(std::string fname)
{
	/*
	The first line indicates the number of vertices and edges,
	respectively. Each subsequent line describes an edge (the first two
	numbers are its tail and head, respectively) and its length (the third
	number). NOTE: some of the edge lengths are negative. NOTE:
	These graphs may or may not have negative-cost cycles.
	*/
	std::fstream fs;
	fs.open(fname);
	if (!fs.is_open()) {
		throw std::runtime_error("Unable to open " + fname + "\n");
	}

	std::string line;
	std::getline(fs, line);
	std::stringstream ss{ line };
	int expected{ 0 };
	ss >> v_;
	double x{ 0 }; double y{ 0 };
	while (getline(fs, line)) {
		ss.clear();
		ss.str(line);
		ss >> x >> y;
		x_.push_back(x);
		y_.push_back(y);
		d_.push_back(std::vector<int>(v_));
	}
	if (x_.size() != v_ || y_.size() != v_) {
		throw std::runtime_error("Data input error in " + fname + "\n");
	}
}

void Graph::setDistances()
{
	for (int j{ 0 }; j < v_; ++j) {
		d_[j][j] = 0;
	}
	for (int j{ 0 }; j < v_; ++j) {
		for (int i{ j + 1 }; i < v_; ++i) {
			double x{ x_[j] - x_[i] };
			double y{ y_[j] - y_[i] };
			d_[j][i] = static_cast<int>(sqrt(x*x + y*y));
			d_[i][j] = d_[j][i];
		}
	}
}

void Graph::printD()
{
	std::cout << "\t";
	for (int j{ 0 }; j < v_; ++j) {
		std::cout << std::setw(5) << static_cast<int>(j);
	}
	std::cout << std::endl;

	for (int j{ 0 }; j < v_; ++j) {
		std::cout << std::setw(4) << static_cast<int>(j) << "\t";
		for (int i{ 0 }; i < v_; ++i) {
			std::cout << std::setw(4) << static_cast<int>(d_[j][i]) << " ";
		}
		std::cout << std::endl;
	}
}

