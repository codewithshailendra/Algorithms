#include "Sat.h"

Sat::Sat(std::string fname, bool isAdj) : fileName_ {fname}, v_{ 0 }, e_{ 0 }, root_{ 0 },
adj_{ std::make_shared<std::map<int, std::vector<int>>>() },
rAdj_{ std::make_shared<std::map<int, std::vector<int>>>() },
id_{}, marked_{}
{
	if (isAdj) {
		getData();
	}
	else {
		getConstraints(); 
	}
	initialise(adj_);
	reverseAdj();
	dfs(rAdj_);
	initialise(rAdj_);
	scc(adj_, reversePost_);
}

void Sat::initialise(std::shared_ptr<std::map<int, std::vector<int>>> const & a) {
	id_.clear();
	marked_.clear();
	for (auto const & v : *a) {
		// first: vertex number - second: adjacency vector
		id_.emplace(v.first, 0);
		marked_.emplace(v.first, false);
	}
}

bool Sat::has(int v)
{
	return adj_->find(v) != adj_->cend();
}

void Sat::addVertex(int v)
{
	if (!has(v)) {
		adj_->emplace(v, std::vector<int>());
	}
}

void Sat::getConstraints() {
	std::fstream fs;
	fs.open(fileName_);
	if (!(fs.is_open())) {
		throw std::runtime_error("Unable to open " + fileName_);
	}

	std::string line;
	int x1{ 0 };
	int x2{ 0 };
	std::getline(fs, line);
	std::stringstream ss{ line };
	int conditions{ 0 };
	ss >> conditions;
	std::cout << conditions << " conditions expected" << std::endl;

	while (std::getline(fs, line)) {
		ss.clear();
		ss.str(line);
		ss >> x1 >> x2;
		addVertex(x1);
		addVertex(-x1);
		addVertex(x2);
		addVertex(-x2);
		adj_->at(-x1).push_back(x2);
		adj_->at(-x2).push_back(x1);
		e_ += 2;
	}
	fs.close();
	v_ = static_cast<int>(adj_->size());
	std::cout << adj_->size() << " nodes and " << e_ << " edges created\n";
}

void Sat::getData() {
	std::fstream fs;
	fs.open(fileName_);
	if (fs.is_open()) {
		std::stringstream ss;
		std::string line;
		int v{ 0 };
		int w{ 0 };
		while (std::getline(fs, line)) {
			ss.clear();
			ss.str(line);
			ss >> v >> w;
			addVertex(v);
			addVertex(w);
			adj_->at(v).push_back(w);;
		}
	}
	fs.close();
}

void Sat::reverseAdj()
{
	for (auto const & mp : *adj_) {
		// first: source vertex number - second: list of adjacencies (destination vertex numbers)
		std::vector<int> adj;
		for (auto const & u : mp.second) {
			adj.push_back(u);
		}
		rAdj_->emplace(mp.first, adj);
	}
}

void Sat::mark(int v)
{
	marked_[v] = true;
}

bool Sat::marked(int v)
{
	if (marked_.find(v) == marked_.cend()) {
		return false;
	}
	return marked_.at(v);
}

void Sat::dfsVisit(std::shared_ptr<std::map<int, std::vector<int>>> const & a, int v)
{
	std::stack<int> stk;
	mark(v);
	stk.push(v);
	while (!stk.empty()) {
		int vv{ stk.top() };
		std::vector<int> adjacencies{ a->at(vv) };
		auto it{ adjacencies.rbegin() };
		while (it != adjacencies.rend()) {
			if (!marked(*it)) {
				mark(*it);
				stk.push(*it);
			}
			it++;
		}
		if (vv == stk.top()) {
			stk.pop();
			std::cout << "Finished " << vv << "\n";
			reversePost_.push(vv);
		}
	}
}

void Sat::dfs(std::shared_ptr<std::map<int, std::vector<int>>> const & a)
{
	for (auto const & v : *a) {
		if (!marked(v.first)) {
			dfsVisit(a, v.first);
		}
	}
}

void Sat::sccVisit(std::shared_ptr<std::map<int, std::vector<int>>> const & a, int v)
{
	std::stack<int> stk;
	mark(v);
	id_[v] = root_;
	stk.push(v);
	int vv{ 0 };
	while (!stk.empty()) {
		vv = stk.top();
		for (auto const & w : a->at(vv)) {
			if (!marked(w)) {
				mark(w);
				id_[w] = root_;
				stk.push(w);
			}
		}
		if (vv == stk.top()) {
			stk.pop();
		}
	}
}

void Sat::scc(std::shared_ptr<std::map<int, std::vector<int>>> const & a, std::stack<int> & stk) {
	root_ = 0;
	int s{ 0 };
	while (!stk.empty()) {
		s = stk.top();
		stk.pop();
		if (!marked(s)) {
			sccVisit(a, s);
			root_++;
		}
	}
	std::cout << "Roots " << root_ << std::endl;
}