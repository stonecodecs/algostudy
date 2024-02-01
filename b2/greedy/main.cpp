#include<iostream>
#include<algorithm>
#include<vector>
#include<tuple>
#include<exception>
#include<sstream>
#include<fstream>
#include<string>

const std::string FILE_PREFIX = "greed_schedule_";

void parseFile(const std::string& filename, std::vector<int>& lengths, std::vector<int>& weights) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    int numJobs;
    file >> numJobs;

    lengths.resize(numJobs);
    weights.resize(numJobs);

    for (int i = 0; i < numJobs; ++i) {
        file >> weights[i] >> lengths[i];
    }

    file.close();
}


// greedy function 1
// when all l are the same, largest weight should be first
// when all w are the same, shortest l should be first
double greedyDiff(std::tuple<int,int,int> a,
                  std::tuple<int,int,int> b) {
    // tiebreaker: favor jobs with larger weights
    if((std::get<2>(a) - std::get<1>(a)) == (std::get<2>(b) - std::get<1>(b))) {
        return std::get<2>(a) > std::get<2>(b);
    }
    // w_a - l_a < w_b - l_b
    return (std::get<2>(a) - std::get<1>(a)) > (std::get<2>(b) - std::get<1>(b));
}

// greedy function 2
double greedyRatio(std::tuple<int,int,int> a,
                   std::tuple<int,int,int> b) {
    return (((double)std::get<2>(a) / (double)std::get<1>(a)) > ((double)std::get<2>(b) / (double)std::get<1>(b)));
}

// Input:
// -- lengths - lengths of job corresponding to job index i = 0...n
// -- weights - weights of job corresponding to job index i = 0...n
// -- greedyf - function 
// Output: job sequence of indicies to do first to last that minimizes weighted completion times
// Warning: will fail when greedy function passed is invalid
std::vector<int> minWeightedSumJobOrdering(const std::vector<int>& lengths, 
                                           const std::vector<int>& weights,
                                           double (*greedy_func)(std::tuple<int,int,int>,
                                                                 std::tuple<int,int,int>)) {

    if(lengths.size() != weights.size()) {
        std::__throw_runtime_error("minWeightedSumJobOrdering: lengths must be equal to weights!");
    }
    int N = lengths.size();
    std::vector<std::tuple<int, int, int>> jobs(N); // group into one vector<index, l, w>
    std::vector<int> order(N); // group into one vector<index, l, w>
    for(int i = 0; i < N; i++) {
        jobs[i] = std::make_tuple(i, lengths[i], weights[i]);
    }

    std::sort(jobs.begin(), jobs.end(), greedy_func);
    std::transform(jobs.begin(), jobs.end(), order.begin(), [](const auto& tuple) { 
        return std::get<0>(tuple);
    });

    return order; // job order
}

// returns weightedSum of jobs
int weightedSum(std::vector<int>& order,
                std::vector<int>& l,
                std::vector<int>& w) {
    if(l.size() != w.size() || order.size() != l.size()) {
        std::__throw_runtime_error("minWeightedSumJobOrdering: lengths must be equal to weights!");
    }
    int sum = 0;
    int time = 0;
    for(int i = 0; i < order.size(); i++) {
        int job = order[i];
        sum += (l[job] + time) * w[job];
        time += l[job];
    }
    return sum;
}

void printVector(std::vector<int> a) {
    for(const int& e : a) { std::cout << e << " "; }
    std::cout << '\n';
}

int main(int argc, char** argv) {
    std::vector<int> l = {1, 2, 3};
    std::vector<int> w = {3, 2, 1};
    parseFile(FILE_PREFIX + "test1.txt", l, w);
    std::vector<int> order_diff = minWeightedSumJobOrdering(l, w, &greedyDiff);
    std::vector<int> order_ratio = minWeightedSumJobOrdering(l, w, &greedyRatio);
    printVector(order_diff);
    printVector(order_ratio);
    std::cout << "weighted sums: \n";
    std::cout << "--greedyDiff: " << weightedSum(order_diff,l,w) << '\n';
    std::cout << "--greedyRatio: " << weightedSum(order_ratio,l,w) << '\n';
    return 0;
}