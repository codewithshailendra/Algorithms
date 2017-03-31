#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <memory>
#include <iterator>

const std::string t{ R"(C:\Users\n419\Repos\Huffman\Huffman\Text.txt)" };
const std::string l{ R"(C:\Users\n419\Repos\Huffman\Huffman\huffman.txt)" };
std::vector<int> getData(std::string const & fname) {

	std::fstream fs;
	fs.open(fname);
	std::string line;
	std::getline(fs, line);
	std::stringstream ss{ line };
	int length{ 0 };
	ss >> length;
	int weight{ 0 };
	std::vector<int> v;
	while (std::getline(fs, line)) {
		ss.clear();
		ss.str(line);
		ss >> weight;
		v.push_back(weight);
	}
	fs.close();
	if (v.size() != length) { std::cout << "Error reading data"; }
	return v;
}

struct hNode;
using phN = std::shared_ptr<hNode>;

struct hNode {
	std::string name;
	int freq;
	phN left;
	phN right;
	std::string prefix;
	hNode(std::string n, int f) : name{ n }, freq{ f }, left{ nullptr }, right{ nullptr }, prefix{ "" } {};
	hNode(phN lhs, phN rhs) : name{ lhs->name + rhs->name }, freq{ lhs->freq + rhs->freq }, left{ lhs }, right{ rhs }, prefix{ "" } {};

};

bool operator<(phN const & lhs, phN const & rhs) {
	return lhs->freq < rhs->freq;
}

class HTree {
public:
	HTree(std::vector<int> data) : nodes_{} {
		int a{ 0 };
		for (auto const & f : data) {
			nodes_.emplace_back(std::make_shared<hNode>( std::to_string(a), f));
			a++;
		}
		buildTree();
		auto p = buildTable(nodes_.at(0));
		showTable(p);
		std::cout << "Min = " << minLen_ << "  Max = " << maxLen_ << std::endl;
	};

	void show() {
		std::cout << "\nNodes\n";
		std::copy(nodes_.cbegin(), nodes_.cend(), std::ostream_iterator<phN>(std::cout, "\n"));
	}

private:
	std::vector<phN> nodes_;
	size_t minLen_{1000000000 };
	size_t maxLen_{ 0 };

	void srt() {
		std::sort(nodes_.begin(), nodes_.end());
		std::reverse(nodes_.begin(), nodes_.end());
	}
	
	void buildTree() {
		while (nodes_.size() > 1) {
			srt();
			auto n1 = nodes_.back();
			nodes_.pop_back();
			auto n2 = nodes_.back();
			nodes_.pop_back();
			nodes_.emplace_back(std::make_shared<hNode>(n1, n2));
		}
	}
	
	phN buildTable(phN p) {
		if (p->left && p->right) {
			p->left->prefix = p->prefix + "0";
			buildTable(p->left);
			p->right->prefix = p->prefix + "1";
			buildTable(p->right);
		}
		return p;
	}

	void showTable(phN p) {
		if (p->left == nullptr && p->right == nullptr) {
			std::cout << p->name << " = " << p->prefix << "\n";
			if (p->prefix.length() < minLen_) { 
				minLen_ = p->prefix.length();
			}
			if (p->prefix.length() > maxLen_) {
				maxLen_ = p->prefix.length(); 
			}
			return;
		}
			showTable(p->left);
			showTable(p->right);
		return;
	}
};

std::ostream & operator<<(std::ostream & os, phN n) {
	std::cout << n->name << " = " << n->prefix << " f = " << n->freq;
	if (n->left) {
		std::cout << " left = " << n->left->name;
	}
	else {
		std::cout << " null";
	}
	if (n->right) {
		std::cout << " right = " << n->right->name;
	}
	else {
		std::cout << " null";
	}
	return os;
}

int main()
{
	HTree huffman(getData(l));
	return 0;
}

