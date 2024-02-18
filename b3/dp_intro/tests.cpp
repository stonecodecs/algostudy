#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
#include<fstream>
#include<sstream>
#include<cmath>
#include<string>
#include<limits.h>
#include"bst.h"
#include"b2/ch8/graph.h"
// #include<gtest/gtest.h>

typedef std::vector<std::vector<int>> matrix;


struct SequenceInput {
    int lenX;
    int lenY;
    int gapCost;
    int mismatchCost;
    std::string sequenceX;
    std::string sequenceY;
};

SequenceInput readInput(const std::string& filename) {
    SequenceInput input;

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    // Read the first line: length of sequence X, space, length of sequence Y
    inputFile >> input.lenX >> input.lenY;

    // Read the second line: gap cost, space, mismatch cost
    inputFile >> input.gapCost >> input.mismatchCost;

    // Read the third line: sequence of X (string)
    inputFile.ignore(); // Ignore newline character left in the input buffer
    std::getline(inputFile, input.sequenceX);

    // Read the fourth line: sequence of Y
    std::getline(inputFile, input.sequenceY);

    return input;
}

std::array<std::array<int, 4>, 4> create_homogenous_penalty_matrix(int p) {
    return {
        {  //A,C,G,T
            {0,p,p,p}, // A
            {p,0,p,p}, // C
            {p,p,0,p}, // G
            {p,p,p,0}  // T 
        }
    };
}

std::tuple<int, std::vector<std::tuple<int, int>>> readKnapsackItemsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return {-1, {}};
    }

    int knapsackSize, numItems;
    file >> knapsackSize >> numItems;

    std::vector<std::tuple<int, int>> items;
    int value, weight;
    for (int i = 0; i < numItems; ++i) {
        file >> value >> weight;
        items.push_back({value, weight});
    }

    file.close();
    return {knapsackSize, items};
}

std::vector<int> readMWISFromFile(const std::string& filename) {
    std::vector<int> integers;
    std::ifstream file(filename);
    if (file.is_open()) {
        int num;
        file >> num; // skip first number
        while (file >> num) {
            integers.push_back(num);
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
    }
    return integers;
}

// i < j, not inclusive for 'j'
int sum(std::vector<int> v, int i, int j) {
    int s{0};
    for(int x = i; x < j; x++) {
        s += v[x];
    }
    return s;
}

void printMatrix(matrix& tab) {
    for(std::vector<int>& row : tab) {
        for(int& e : row) {
            std::cout << e << " ";
        }
        std::cout << '\n';
    }
}

// memoization -> top-down (recursion)
// tabulation -> bottom up (iterative)
// stick with tabulation here
std::tuple<int, std::vector<int>> mwis(const std::vector<int>& set) {
    std::vector<int> tab(set.size() + 1, 0); // dp

    // 1. find subproblems --
    // optimal(G_n) only depends on the two subproblems
    // include last (n) + optimal(G_n-2)
    // exclude last (n) = optimal(G_n-1)

    if(set.size() > 0) { tab[1] = set[0]; }
    for(int i = 2; i < tab.size(); i++) {
         // 2. show how to solve larger subproblems given solutions to smaller ones --
        // can find from induction that to solve for G_n on it's 3rd to last node is
        // simply the same as the above problem, but for G_n-1 (looks for G_n-2, G_n-3)
        // to determine its inclusion
        tab[i] = std::max(tab[i - 2] + set[i-1], tab[i - 1]);
    }

    // 3. combine subproblems to arrive at the final, larger, original problem
    return std::make_tuple(tab[set.size()], tab);
}

// reconstructs the included weights of mwis given the tabulation table
std::vector<int> mwis_reconstruction(const std::vector<int>& set, const std::vector<int>& tab) {
    std::vector<int> sequence{};
    // from top-down
    // [0,4,8,11,14,14,15]
    for(int i = tab.size() - 1; i >= 0; i--) {
        if(tab[i] != tab[i-1]) { // case 1: optimal(G_n-2) + w_n
            sequence.push_back(set[i-1]);
            i--;
        }
    }

    std::reverse(sequence.begin(), sequence.end());
    return sequence;
}

std::tuple<int, std::vector<std::vector<int>>> knapsack(
    const std::vector<int>& value,  // value of each item
    const std::vector<int>& sizes,  // size of each item
    int C                           // total capacity
) {
    if(value.size() != sizes.size()) { 
        throw std::runtime_error("knapsack requires value and sizes vectors to be equal in size");
    }
    std::vector<std::vector<int>> tab;
    tab.resize(C + 1, std::vector<int>(value.size() + 1)); // C+1 x N+1 matrix

    // 1. similar to MWIS; optimal(S_n) is made from:
    // either, optimal(S_n-1, C) OR (optimal(S_n-2) + item_n_value, C - item_n_size)

    // base cases where capacity = 0, or no items (= 0 value)
    for(int i = 0; i < tab.size(); i++) { tab[i][0] = 0; } 
    for(int i = 0; i < tab[0].size(); i++) { tab[0][i] = 0; } 

    // now fill tabulation table (bottom up)
    for(int i = 1; i < tab.size(); i++) {           // 'i' indicates value of C for subproblem [i,j]
        for(int j = 1; j < tab[i].size(); j++) {    // 'j-1' indicates index of item in list
            if(sizes[j - 1] > i) {                      // exclude -- item doesn't fit; over-capacity
                tab[i][j] = tab[i][j-1]; 
                continue;
            }

            if((i - sizes[j-1]) >= 0) {
                tab[i][j] = std::max(tab[i - sizes[j-1]][j - 1] + value[j - 1], tab[i][j-1]);
            }
        }
    }

    return std::make_tuple(tab[C][value.size()], tab); // value, table
}

// list of the index of items to take based on the tab given by the knapsack tab
std::vector<int> knapsack_reconstruction(
    const std::vector<int>& value,
    const std::vector<int>& sizes,
    const std::vector<std::vector<int>>& tab
) {
    std::vector<int> items{};
    int i{static_cast<int>(tab.size() - 1)}, j{static_cast<int>(tab[0].size() - 1)};

    while(i >= 0 && j >= 0) {
        // exclude case
        if(tab[i][j] != tab[i][j-1]) {
            items.push_back(j - 1);
            i -= sizes[j - 1];
        }
        j--;
    }
    return items;
}

std::tuple<int, matrix, matrix> minimum_weight_BST(
    std::vector<int>& weights       // index will be the arbitrary 'keys'
) {
    matrix tab{};
    matrix roots{};
    tab.resize(weights.size() + 1, std::vector<int>(weights.size() + 1));
    roots.resize(weights.size() + 1, std::vector<int>(weights.size() + 1));

    // empty tree case i == j
    for(int i = 0; i < tab.size(); i++) {
        tab[i][i] = 0;
        roots[i][i] = -1;
    }

    for(int s = 0; s < tab.size(); s++) {
        for(int i = 0; i < tab.size() - s - 1; i++) {
            int j = i + s + 1; // tab[i,j] where i = j-1 is a "1 node tree" situation
            int minTreeValue{INT_MAX};
            int minTreeRoot{i};
            
            for(int it = i; it < j; it++) {
                int treeVal = tab[i][it] + tab[it + 1][j];
                if(treeVal < minTreeValue) {
                    minTreeValue = treeVal;
                    minTreeRoot = it;
                }
            }
            tab[i][j] = sum(weights, i, j) + minTreeValue;
            roots[i][j] = minTreeRoot;  // = -1 means empty
        }
    }

    return std::make_tuple(tab[0][weights.size()], tab, roots);
}


TreeNode* _minimum_weight_BST_reconstruction(
    matrix& tab,
    matrix& roots,
    int start,
    int end
) {
    TreeNode* root{NULL};
    int i = start;   
    int j = end;
    if(roots[i][j] == -1) {
        return NULL;
    }

    root = new TreeNode(roots[i][j]); // root chosen at tab[i][j]
    root->left = _minimum_weight_BST_reconstruction(tab, roots, i, roots[i][j]);
    root->right = _minimum_weight_BST_reconstruction(tab, roots, roots[i][j] + 1, j);

    return root;
}

// do later
BinarySearchTree* minimum_weight_BST_reconstruction(
    matrix& tab,
    matrix& roots
) {
    return new BinarySearchTree(_minimum_weight_BST_reconstruction(tab, roots, 0, tab.size()-1));
}

std::tuple<int, matrix> minimum_penalty_genomic_sequence(
    std::string& a,
    std::string& b,
    std::array<std::array<int, 4>, 4>& pair_penalty, // ACGT 4x4
    int gap_penalty                                 // must be non-negative
) {
    std::unordered_map<char, int> map{
        {'A', 0},
        {'C', 1},
        {'G', 2},
        {'T', 3}
    };
    std::string min_a{};
    std::string min_b{};
    matrix tab{};
    tab.resize(a.length() + 1, std::vector<int>(b.length() + 1));

    // 1. subproblems: 
    // optA(n-1), optB(n) + A,_
    // optA(n), optB(n-1) + _,B
    // optA(n-1), optB(n-1) + A,B
    // then, either add the minimum penality of these cases

    // base case: string of "gaps" vs any other string = string length * gap_penalty
    for(int i = 0; i < a.length() + 1; i++) { tab[i][0] = i * gap_penalty; }
    for(int j = 0; j < b.length() + 1; j++) { tab[0][j] = j * gap_penalty; }

    for(int i = 1; i < tab.size(); i++) {
        for(int j = 1; j < tab[i].size(); j++) {
            // min_penalty, case 0/1/2
            std::vector<int> cases = {
                tab[i-1][j-1] + pair_penalty[map[a[i-1]]][map[b[j-1]]], // it's [i,j] but -1 to correct for indexing
                tab[i-1][j] + gap_penalty,
                tab[i][j-1] + gap_penalty
            };

            tab[i][j] = *std::min_element(cases.begin(), cases.end());
        }
    }

    return std::make_tuple(tab[a.length()][b.length()], tab);
}

std::tuple<std::string, std::string> genomic_reconstruction(
    std::string& a,
    std::string& b,
    matrix& tab,
    std::array<std::array<int, 4>, 4>& pair_penalty,
    int gap_penalty
) {
    std::string min_a = "";
    std::string min_b = "";
    std::unordered_map<char, int> map{
        {'A', 0},
        {'C', 1},
        {'G', 2},
        {'T', 3}
    };

    int i{static_cast<int>(a.size())};
    int j{static_cast<int>(b.size())};

    while(i > 0 && j > 0) {
        int curr = tab[i][j];
        // TODO: figure this out 
        // curr - pairpenalty (path) from priority descending: [-1,-1], [-1,0], [0,-1]
        if(tab[i-1][j-1] == curr - pair_penalty[map[ a[i-1] ]][map[ b[j-1] ]]) {
            min_a = a[i-1] + min_a;
            min_b = b[j-1] + min_b;
            i--; j--;
            continue;
        }

        if(tab[i-1][j] == curr - gap_penalty) {
            min_a = a[i-1] + min_a;
            min_b = "_" + min_b;
            i--;
            continue;
        }

        if(tab[i][j-1] == curr - gap_penalty) {
            min_a = "_" + min_a;
            min_b = b[j-1] + min_b;
            j--;
            continue;
        }
    }
    if(i > 0) {
        min_a = a[i-1] + min_a;
        min_b = "_" + min_b;
    }
    if(j > 0) {
        min_a = "_" + min_a;
        min_b = b[j-1] + min_b;
    }

    return {min_a, min_b};
}

typedef std::unordered_map<int,std::vector<std::tuple<int, int>>> adjlist_in;

adjlist_in incomingEdgeMatrix(Graph<int>* g) {
    if(g == nullptr) { return {}; }
    adjlist_in incoming = {};
    std::vector<int> verts = g->getVertices();
    for(auto& v : verts) {
        auto ws = g->getNeighbors(v);
        if(incoming.find(v) == incoming.end()) { incoming[v] = {}; }
        for(auto& w : ws) {
            if(incoming.find(w.first) == incoming.end()) {
                incoming[w.first] = {};
            }
            incoming[w.first].push_back({v, w.second});
        }
    }

    return incoming;
} 

std::tuple<std::vector<int>, matrix> bellman_ford(
    int s,
    Graph<int>* g
) {
    matrix tab{};
    std::unordered_map<int,int> index_map{}; // keys to tab's index
    adjlist_in inc_neighbors_for = incomingEdgeMatrix(g); // incoming edges for vertices
    std::vector<int> verts = g->getVertices();
    tab.resize(verts.size() + 1, std::vector<int>(verts.size(), 0));
    for(int i = 0; i < verts.size(); i++) {
        index_map[verts[i]] = i;
        tab[0][i] = INT_MAX;
    }

    tab[0][index_map[s]] = 0;

    // i represents "edge budget"
    // j represents "vertex"
    for(int i = 1; i < tab.size(); i++) {
        bool stable{true};
        for(int j = 0; j < tab[i].size(); j++) {
            auto j_incoming = inc_neighbors_for[verts[j]]; // vector of tuples (fromvertex, weight)
            if(j_incoming.empty()) { // no neighbors, no change
                tab[i][j] = tab[i-1][j];
                continue;
            }
            int smallest{INT_MAX};
            for(auto& n : j_incoming) {
                auto [v, len] = n;
                int index_of_v = index_map[v];
                if(tab[i-1][index_of_v] < INT_MAX && (tab[i-1][index_of_v] + len) < smallest) {
                    smallest = tab[i-1][index_of_v] + len;
                }
            }
            tab[i][j] = std::min(tab[i-1][j], smallest);
            if(tab[i-1][j] != tab[i][j]) { stable = false; }
        }
        if(stable) {
            return {tab[i-1], tab};
        }
    }

    return {{}, tab}; // we'll say empty vector indicates a negative cycle
}

// 
int main(int argc, char** argv) {
    std::vector<int> set = readMWISFromFile("test_mwis.txt");
    auto [weight, tab] = mwis(set);
    // tab should be => [0,4,8,11,14,14,15] -> reconstructed to 8,6,1 = 15
    std::cout << weight << '\n';
    std::vector<int> sequence = mwis_reconstruction(set, tab);
    for(int& e : sequence) {
        std::cout << e << " ";
    }
    std::cout << '\n';

    // std::vector<int> values = {2,3,3,6,2};
    // std::vector<int> sizes  = {2,3,2,4,1};
    // int C = 4;

    std::vector<int> values{};
    std::vector<int> sizes{};
    auto [C, testdata] = readKnapsackItemsFromFile("test_knapsack.txt");
    for(auto& data : testdata) {
        values.push_back(std::get<0>(data));
        sizes.push_back(std::get<1>(data));
    }

    auto [totval, matrix] = knapsack(values, sizes, C);
    std::vector<int> sack = knapsack_reconstruction(values, sizes, matrix);
    std::cout << "items in knapsack: ";
    for(int& e : sack) {
        std::cout << e << " ";
    }
    std::cout << '\n';

    // std::reverse(matrix.begin(), matrix.end());
    std::cout << "\nknapsack: " << totval << std::endl;
    std::vector<int> bst_weights = {
        2,8,2,5,5,2,8,3,6,1,
        1,6,3,2,6,7,4,63,2,9,
        10,1,60,5,2,7,34,11,31,
        76,21,6,8,1,81,37,15,6,
        8,24,12,18,42,8,51,21,8,6,5,7};

    // std::vector<int> bst_weights = {1,2,2,1,3,4};
    auto [bst_val, bst_matrix, roots] = minimum_weight_BST(bst_weights);
    std::cout << "\nmin_bst_weights: " << bst_val << std::endl;
    // printMatrix(bst_matrix);
    // std::cout << std::endl;
    // printMatrix(roots);

    BinarySearchTree* bst_actual = minimum_weight_BST_reconstruction(bst_matrix, roots);
    bst_actual->levelTraversal();
    std::cout << "\nbst_weighted_sum: " << bst_actual->weightedSum(bst_weights) << std::endl;
    delete bst_actual;

    std::array<std::array<int, 4>, 4> penalty_matrix = create_homogenous_penalty_matrix(3);
    std::string a = "AGT";
    std::string b = "GCT";

    auto [seq_penalty, seqmat] = minimum_penalty_genomic_sequence(a, b, penalty_matrix, 1);
    std::cout << "\nmin sequence penalty: " << seq_penalty << std::endl;
    printMatrix(seqmat);

    auto [min_a, min_b] = genomic_reconstruction(a,b,seqmat,penalty_matrix, 1);
    std::cout << "\nstr1: " << min_a << "\nstr2: " << min_b << std::endl;

    SequenceInput seq_test_data = readInput("test_sequence.txt");
    auto penalty_matrix_test = create_homogenous_penalty_matrix(seq_test_data.mismatchCost);
    auto [seq_penalty2, seqmat2] = minimum_penalty_genomic_sequence(
        seq_test_data.sequenceX,
        seq_test_data.sequenceY,
        penalty_matrix_test,
        seq_test_data.gapCost
    );

    std::cout << "\nmin sequence penalty(test): " << seq_penalty2 << std::endl;

    auto [test_a, test_b] = genomic_reconstruction(
        seq_test_data.sequenceX,
        seq_test_data.sequenceY,
        seqmat2,
        penalty_matrix_test,
        seq_test_data.gapCost
    );

    std::cout << "\nstr1(test): " << test_a << "\nstr2(test): " << test_b << std::endl;    

    Graph<int>* g = new Graph<int>(true, true); // directed, weighted
    for(int i = 0; i < 5; i++) {
        g->addNode(i);
    }
    // g->addEdge(0,1,1);
    // g->addEdge(1,2,-2);
    // g->addEdge(2,3,-3);
    // g->addEdge(3,1,-1);
    // g->addEdge(1,4,4);
    g->addEdge(0,1,1);
    g->addEdge(1,2,2);
    g->addEdge(1,3,6);
    g->addEdge(0,2,4);
    g->addEdge(2,3,3);
    g->printAdjList();
    auto [bf_result, bf_tab] = bellman_ford(0, g);
    std::cout << "\nresults: " << (bf_result.empty() ? "negative cycle" : "");
    for(int& b : bf_result) {
        std::cout << b << " ";
    }
    std::cout << '\n';
    printMatrix(bf_tab);
    delete g;
    return 0;
}