#include "Heap.h"
#include "Vertex.h"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <memory>

const std::string data{ R"(C:\Users\n419\Repos\Dijkstra\Dijktra\dijkstraData.txt)" };
const std::string test{ R"(C:\Users\n419\Repos\Dijkstra\Dijktra\data.txt)" };

constexpr int inf{ INT_MAX };

using vMap = std::map<size_t, Vertex>;
using vertices = std::shared_ptr<vMap>;

vertices GetData(std::string src) {
	std::string line;
	std::ifstream file(src);
	vertices result = std::make_shared<vMap>();

	size_t vertex{ 0 };
	int weight{ 0 };
	size_t head{ 0 };
	char comma;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			ss >> vertex;
			Vertex v(vertex);
			while (ss >> head >> comma >> weight) {
				v.addEdgeTo(head, weight);
			}
			result->insert({v.vertex(), v });
		}
	}
	file.close();
	return result;
}

void showData(vertices graph) {
	for (auto const & v : *graph) {
		v.second.showScore();
	}
}

void showAnswer(vertices graph) {
	std::vector<size_t> vertex {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
	for (auto const & v : vertex) {
		graph->at(v).showScore();
	}
}

int main()
{
	vertices VX{ GetData(data) };
	//showData(V_X);
	vertices X = std::make_shared<vMap>();

	size_t bestNode{ VX->cbegin()->first };   // the starting node
	X->insert({ bestNode,VX->at(bestNode) });
	VX->erase(bestNode);
	int minScore{ inf };  // the "not connected" weight
	int score{ 0 };
	while (!VX->empty()) {
		for (auto & v : *X) {
			for (auto const & edge : v.second.edges()) {
				if (VX->find(edge.first) != VX->cend()) { // the node edge.first is in V_X so we need to calculate its score
					//std::cout << "Node " << v.first << " edge " << edge.first << std::endl;
					score = v.second.score() + edge.second;
					if (score < minScore) {
						minScore = score;
						bestNode = edge.first;
					}
				}
			}
		}
		// move node with best Dijksta score into X
		X->insert({ bestNode,VX->at(bestNode) });
		VX->erase(bestNode);
		X->at(bestNode).setScore(minScore);
		//std::cout << "Best node was node " << bestNode << " with a score of " << X->at(bestNode).score() << std::endl;
		minScore = inf;  // the "not connected" weight
	}

	showAnswer(X);

	return 0;
}

