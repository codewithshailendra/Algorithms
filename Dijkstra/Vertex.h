#pragma once
#include <map>
#include <iostream>

class Vertex {

public:
	Vertex(size_t u) : vertex_{ u }, edge_{}, dScore_{ 0 }, position_{ 0 } {
	}

	void addEdgeTo(size_t head, int weight) {
		if (edge_.find(head) != edge_.cend()) {
			std::cout << "********************** Parallel Path Found ********************\n";
		}
		else {
			edge_.insert({ head, weight });
		}
	}

	int weightOf(size_t head) {
		auto it{ edge_.find(head) };
		if (edge_.find(head) == edge_.cend()) {
			std::cout << "************************** EDGE NOT FOUND ************************\n";
			return 0;
		}
		else {
			return it->second;
		}
	}

	size_t vertex() { return vertex_; }

	int score() { return dScore_; }

	void setScore(int score) { dScore_ = score; }

	int position() { return position_; }

	void setPosition(size_t pos) { position_ = pos; }

	void show() const {
		std::cout << "Node " << vertex_ << ":\tscore = " << dScore_ << /* "\tposition = " << position_ << */ "\n";
		auto it{ edge_.cbegin() };
		while (it != edge_.cend()) {
			std::cout << "\t" << it->first << " - " << it->second << "\n";
			it++;
		}
	}

	void showScore() const {
		std::cout << "Node " << vertex_ << ":\tscore = " << dScore_ << /* "\tposition = " << position_ << */ "\n";
	}

	std::map<size_t, int> const & edges() {
		return edge_;
	}

private:
	size_t vertex_;
	std::map<size_t, int> edge_;
	int dScore_;
	size_t position_;

};

