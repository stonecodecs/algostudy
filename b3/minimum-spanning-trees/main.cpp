#include<iostream>
#include<vector>
#include<tuple>
#include<string>
#include<unordered_set>
#include<fstream>
#include<sstream>
#include<limits>
#include"b2/ch8/heap.h"
#include"b2/ch8/graph.h"

typedef std::tuple<int, int> edge; // vertices<v,w>

// creates and returns a pointer to a graph generated from the file 'filename'
Graph<int>* graphFromFile(std::string filename) {
    Graph<int>* g = new Graph<int>(false,true);

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        throw std::runtime_error("Could not open file.");
    }

    // Read the first line with two numbers
    int numV, numE;
    if (!(file >> numV >> numE)) {
        std::cerr << "Failed to read the first line." << std::endl;
        throw std::runtime_error("Could not read file.");
    }

    for(int i = 1; i <= numV; i++) {
        g->addNode(i);
    }

    // Read the remaining lines with three numbers each
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int v1, v2, weight;
        if (!(iss >> v1 >> v2 >> weight)) {
            std::cerr << "Failed to read a line with three numbers." << std::endl;
            continue;
        }
        g->addEdge(v1,v2,weight);
    }

    file.close();
    return g;
}

int mst_score(Graph<int>* g, std::vector<edge>& edges) {
    int score{0};
    for(edge e : edges) {
        auto [v, w] = e;
        int* weight_vw = g->getWeight(v,w);
        if(weight_vw == nullptr) {
            std::cerr << "Edge not found in graph.\n";
        }
        score += *weight_vw;
    }
    return score;
}

// give edges of minimum spanning tree
// assumes graph 'g' is fully connected
std::vector<edge> prim(Graph<int>* g) {
    typedef std::tuple<int, edge*> we_pair; // weight edge pair <int: weight, *edge: (v,w)>

    Heap<int> h{};
    std::vector<edge> mstEdges{};
    std::vector<int> vertices = g->getVertices();
    std::unordered_map<int, we_pair> edges{}; // <vertex w, <minimum distance,(v,w)>>
    // given vertex w-> edge(v,w) (replace with newest best edge for vertex)
    std::unordered_set<int> X{}; // stores vertices

    if(vertices.size() <= 1) { return mstEdges; } // empty vector

    X.insert(vertices[0]);   // arbitrary starting vertex
    std::unordered_map<int,int> initial_neighbors = g->getNeighbors(vertices[0]);

    // "heapify"
    for(int i = 1; i < vertices.size(); i++) {
        if(X.find(vertices[i]) == X.end()) { // not in X
            int heapkey{0}; // edge weight = key of heap
            edge* vw{NULL};

            if(initial_neighbors.find(vertices[i]) != initial_neighbors.end()) { // edge exists
                heapkey = initial_neighbors[vertices[i]]; // weight of edge
                vw = new edge(vertices[0], vertices[i]); // edge endpoints
            } else {
                heapkey = INT_MAX;
                vw = NULL;
            }
            edges[vertices[i]] = we_pair(heapkey, vw);
            h.insert(heapkey, vertices[i]);
        }
    }

    while(!h.isEmpty()) {
        auto [weight, v] = h.extractTop();  // int: edge weight, int: vertex
        X.insert(v);
        // update edges
        if(std::get<1>(edges[v]) != nullptr) {
            mstEdges.push_back(*std::get<1>(edges[v])); // add copy of min edge for v
            delete std::get<1>(edges[v]);
            std::get<1>(edges[v]) = nullptr;
        }
        std::get<0>(edges[v]) = weight;             // update min weight for v
        std::unordered_map<int,int> neighbors_of_v = g->getNeighbors(v); // <value, weight>

        // for all neighbors of vertex w, update heap based on unprocessed edges from w
        for(auto it = neighbors_of_v.begin(); it != neighbors_of_v.end(); it++) {
            // it->first is index of endpoint 'w' of (v,w)
            // it->second is the weight from v->w
            if(X.find(it->first) == X.end()) { // if 'w' not already processed in X
                auto [curr_weight_to_w, curr_edge_vw] = edges[it->first]; // current minimums in edges
                if(it->second < curr_weight_to_w) {
                    h.remove(it->first); // remove 'w' value from heap
                    delete curr_edge_vw;
                    curr_edge_vw = nullptr;
                    edges[it->first] = we_pair(it->second, new edge(v,it->first));
                    h.insert(it->second, it->first); // then update back
                }
            }
        }
    }

    return mstEdges;
}

void printVectorEdges(std::vector<edge> a) {
    for(edge e : a) {
        auto [v,w] = e;
        std::cout << "(" << v << ", " << w << ") ";
    }
}

int main() {
    Graph<int>* g; // undirected, weighted
    g = graphFromFile("test2.txt");
    g->printAdjList();
    std::vector<edge> mstEdges = prim(g);
    printVectorEdges(mstEdges);
    std::cout << "mst_score: " << mst_score(g, mstEdges);
    delete g;
    return 0;
}