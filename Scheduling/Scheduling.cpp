#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>

using namespace std;

struct Job {
	int id;
	double w;
	double l;
	double diff;
	double compTime;
	double wct;
};

bool operator<(Job const & lhs, Job const & rhs) {
	bool result{ lhs.diff < rhs.diff };
	//cout << lhs.diff << " < " << rhs.diff << " " << boolalpha << result << "\n";
	return result;
}

ostream & operator<<(ostream& os, Job j) {
	cout << j.id << " " << j.w << " " << j.l << " " << j.diff;
	return os;
}

int main()
{
	vector<Job> job;
	fstream fs;
	fs.open(R"(C:\Users\n419\Repos\Stfd2\Scheduling\jobs)");
	if (!(fs.is_open())) { cout << R"(Unable to open file)" << endl;  exit(-1); }

	string line;
	std::getline(fs, line);
	stringstream ss{ line };
	double jobs{ 0 };
	ss >> jobs;
	if (jobs == 0) { cout << R"(No jobs found)" << endl; exit(-2); }
	cout << jobs << " jobs found\n";
	int i{ 1 };
	while (std::getline(fs, line)) {
		stringstream s{ line };
		double w{ 0 };
		double l{ 0 };
		s >> w >> l;
		Job j{ i++, w, l, w / l, 0, 0 };
		job.push_back(j);
	}

	if (!(job.size() == jobs)) { cout << R"(Error reading jobs)" << endl; exit(-3); }

	//order jobs by decreasing diff
	priority_queue <Job, vector<Job>, std::less<Job>> jobQ(job.begin(), job.end());

	Job nextJob;
	double completionTime{ 0 };
	double totalWeight{ 0 };

	// while there are more jobs
	while (!jobQ.empty()) {
		nextJob = jobQ.top();
		jobQ.pop();

		double d{ nextJob.diff };
		vector<Job> ties;
		ties.push_back(nextJob);

		while (!jobQ.empty() && (jobQ.top().diff == d)) {
			ties.push_back(jobQ.top());
			jobQ.pop();
		}

		sort(ties.begin(), ties.end(), [&](Job lhs, Job rhs) { return lhs.w > rhs.w; });

		for (auto & e : ties) {
			completionTime += e.l;
			e.compTime = completionTime;
			e.wct = e.w * e.compTime;
			totalWeight += e.wct;
			//cout << e << " total = " << totalWeight << endl;
		}
	}

	//cout << endl;
	//copy(result.begin(), result.end(), ostream_iterator<Job>(cout, "\n"));
	cout << endl;
	cout << "Weighted completion times = " << fixed << totalWeight << "\n";
	if (totalWeight < INT_MAX) { cout << "As an integer = " << static_cast<int>(totalWeight) << endl; }

	//char c;
	//cin >> c;
	return 0;
}

