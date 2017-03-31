#include "Graph.h"

Graph::Graph(int v) :
	fileName_{ "" }, v_{ 0 }, e_{ 0 }, root_{ 0 },
	adj_{ std::make_shared<std::map<int, std::vector<int>>>() },
	marked_{}, id_{}, nodesPerComponent_{}, componentSizes_{},
	pre_{}, post_{}, reversePost_{}, stk_{ std::make_shared<std::stack<int>>() }
{
}

Graph::Graph(std::string fname) :
	fileName_{ fname }, v_{ 0 }, e_{ 0 }, root_{ 0 },
	adj_{ std::make_shared<std::map<int, std::vector<int>>>() },
	marked_{}, id_{}, nodesPerComponent_{}, componentSizes_{},
	pre_{}, post_{}, reversePost_{}, stk_{ std::make_shared<std::stack<int>>() }
{
}

void Graph::getData() {
	resetData();
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
			addEdge(v, w);
		}
	}
	fs.close();
}

void Graph::getReverseData() {
	resetData();
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
			addEdge(w, v);
		}
	}
	fs.close();
}

void Graph::getConstraints() {
	resetData();
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

void Graph::getReverseConstraints() {
	resetData();
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
		adj_->at(x1).push_back(-x2);
		adj_->at(x2).push_back(-x1);
		e_ += 2;
	}
	fs.close();
	v_ = static_cast<int>(adj_->size());
	std::cout << adj_->size() << " nodes and " << e_ << " edges created\n";
}

bool Graph::has(int v)
{
	return adj_->find(v) != adj_->cend();
}

Graph::~Graph()
{
}

void Graph::checkContraints()
{
	bool sat{ true };
	auto up = id_.cbegin();
	auto down = id_.cend();
	down--;
	while ((*up).first < (*down).first) {
		if ((*up).second == (*down).second) {
			std::cout << fileName_ << " is not satisfiable at " << (*up).first << " and " << (*down).first << "\n";
			std::cout << " check " << id_[(*up).first] << "  " << id_[(*down).first] << "\n";
			sat = false;
		}
		up++;
		down--;
	}
	if (sat) { std::cout << fileName_ << " is satisfiable\n"; }
}

int Graph::E()
{
	return e_;
}

void Graph::addVertex(int v)
{
	if (!has(v)) {
		adj_->emplace(v, std::vector<int>());
	}
}

void Graph::addEdge(int v, int w)
{
	addVertex(v);
	addVertex(w);
	adj_->at(v).push_back(w);
	e_++;
}

std::string Graph::toString()
{
	std::stringstream ss;
	ss << V() << " vertices and " << E() << " edges\n";
	for (auto const & vertex : *adj_) {
		ss << vertex.first << " : ";
		std::copy(vertex.second.cbegin(), vertex.second.cend(), std::ostream_iterator<int>(ss, ", "));
		ss << "\n";
	}
	return ss.str();
}

void Graph::mark(int v)
{
	marked_[v] = true;
}

// Stack approach
void Graph::dfsOrder2(int v) {
	std::stack<int> stk;
	stk.push(v);
	while (!stk.empty()) {
		int vv{ stk.top() };
		for (auto const & w : adj_->at(vv)) {
			if (!marked(w)) {
				std::cout << "\tNode " << vv << " adjacency " << w << "\n";
				mark(w);
				stk.push(w);
			}
		}
		if (stk.top() == vv) {
			stk.pop();
			std::cout << "\tReversePost + Node " << v << "\n";
			reversePost_.push(vv);
			post_.push(vv);
		}
	}
}

void Graph::dfsOrder3(int v) {
	std::stack<int> stk;
	mark(v);
	stk.push(v);
	while (!stk.empty()) {
		int vv{ stk.top() };
		std::vector<int> adjacencies{ adj_->at(vv) };
		auto it{ adjacencies.rbegin() };
		while (it != adjacencies.rend()) {
			if (!marked(*it)) {
				//std::cout << "Node " << vv << " adjacency " << *it << "\n";
				mark(*it);
				stk.push(*it);
			}
			it++;
		}
		if (vv == stk.top()) {
			stk.pop();
			//std::cout << "Finished " << vv << "\n";
			reversePost_.push(vv);
		}
	}
}
// End of stack approach

void Graph::dfsOrder(int v)
{
	//pre_.push(v);
	mark(v);
	for (auto const & w : adj_->at(v)) {
		if (!marked(w)) {
			//std::cout << "Node " << v << " adjacency " << w << "\n";
			dfsOrder(w);
		}
	}
	//post_.push(v);
	//std::cout << "\tReversePost + Node " << v << "\n";
	reversePost_.push(v);
}

void Graph::reverseDFS()
{
	for (auto const & v : *adj_) {
		if (!marked(v.first)) {
			dfsOrder3(v.first);
		}
	}
	//std::cout << "Finished\n";
}

void Graph::dfs2(int v)
{
	while (!stk_->empty()) { stk_->pop(); }
	mark(v);
	id_[v] = root_;
	stk_->push(v);
	int vv{ 0 };
	while (!stk_->empty()) {
		vv = stk_->top();
		for (auto const & w : adj_->at(vv)) {
			if (!marked(w)) {
				mark(w);
				id_[w] = root_;
				stk_->push(w);
			}
		}
		if (vv == stk_->top()) {
			stk_->pop();
		}
	}
}

void Graph::dfs(int v)
{
	mark(v);
	id_[v] = root_;
	for (auto const & w : adj_->at(v)) {
		if (!marked(w)) {
			dfs(w);
		}
	}
}

void Graph::kccDFS()
{
	int s{ 0 };
	while (!reversePost_.empty()) {
		s = reversePost_.top();
		reversePost_.pop();
		if (!marked(s)) {
			dfs2(s);
			root_++;
		}
	}
	std::cout << "Roots " << root_ << std::endl;
}

int Graph::V()
{
	return static_cast<int>(adj_->size());
}

void Graph::resetData()
{
	v_ = 0;
	e_ = 0;
	root_ = 0;
	adj_->clear();
	marked_.clear();
	id_.clear();
	nodesPerComponent_.clear();
}

bool Graph::marked(int v)
{
	if (marked_.find(v) == marked_.cend()) {
		return false;
	}
	return marked_.at(v);
}

bool Graph::stronglyConnected(int v, int w)
{
	if (id_.find(v) == id_.cend() || id_.find(w) == id_.cend()) { return false; }
	return id_.at(v) == id_.at(w);
}

int Graph::id(int v)
{
	if (id_.find(v) == id_.cend()) {
		std::cout << " Returning a zero id !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	}
	return id_.at(v);
}

int Graph::componentCount()
{
	counts();
	return root_;
}

void Graph::counts()
{
	nodesPerComponent_.clear();
	componentSizes_.clear();

	for (int i{ 0 }; i < root_; ++i) { nodesPerComponent_.emplace(i, 0); }

	for (auto const & v : id_) {
		nodesPerComponent_.at(v.second) += 1;
	}

	//std::cout << "\nOrdered by component number\n";
	for (auto const & component : nodesPerComponent_) {
		//std::cout << "Component " << component.first << " has " << component.second << " nodes \n";
		componentSizes_.emplace(component.second, component.first);
	}

	//std::cout << "\nOrdered by size\n";
	for (auto const & component : componentSizes_) {
		//std::cout << "Component " << component.second << " has " << component.first << " nodes \n"; 
	}
}

std::multimap<int, int, std::greater<int>> Graph::topComponents(int top) {

	std::multimap<int, int, std::greater<int>> topComps;
	auto it = componentSizes_.cbegin();
	top = std::min(top, static_cast<int>(componentSizes_.size()));
	while (top != 0) {
		topComps.emplace(it->first, it->second);
		it++;
		top--;
	}
	return topComps;
}

void Graph::clear()
{
	adj_->clear();
}
