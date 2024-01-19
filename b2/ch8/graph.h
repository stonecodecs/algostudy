#ifndef GRAPH_H
#define GRAPH_H

#include"node.h"
#include<tuple>
#include<limits.h>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<stack>

// will use adjacency lists (not matrix)
template <typename T> 
class Graph {
    private:
        std::vector<Node<T>*> vertices; // real data stored here
        std::vector<std::unordered_map<int, int>> adjList; // map<ID, weight>
        bool isDirected;
        bool isWeighted;
        std::vector<int> _bfs( std::vector<bool>& visited,
                               std::queue<int>& q,
                               std::vector<int>& bfs_list );
        std::vector<int> _augmented_bfs( std::vector<bool>& visited,
                                         std::queue<int>& q,
                                         std::vector<int>& dists );
        std::vector<int> _toposort(std::vector<bool>& visited, std::vector<int>& labels, int& currLabel, int s);
        std::vector<int> dfs_scc(std::vector<bool>& visited, std::vector<int>& SCCgroups, int& currSCC, int v);
    public:
        Graph(bool directed=false, bool weighted=false);
        ~Graph();
        void matrixToGraph(std::vector<std::vector<T>> m);
        void addNode(T val);
        Node<T>* getNode(int id);
        bool addEdge(int v, int w, int weight=1);
        bool remEdge(int v, int w);
        void printAdjList();

        // algos:
        // should be outside class, but yolo
        std::vector<int> bfs(int s);
        std::vector<int> augmented_bfs(int s);
        std::vector<int> UCC(); // connected components
        std::vector<int> dfs(int s);
        std::vector<int> toposort();
        Graph<T> reversedGraph(); // produces G-rev for kosaraju
        std::vector<int> kosaraju();
        std::vector<int> dijkstra(int s); // RETURN to this for HEAP-based for better performance (and prob9.7)
};

template <typename T>
Graph<T>::Graph(bool directed, bool weighted) 
    : isDirected(directed), isWeighted(weighted),
    vertices(std::vector<Node<T>*>()), 
    adjList(std::vector<std::unordered_map<int,int>>()) {}


template <typename T>
Graph<T>::~Graph() {
    for (Node<T>* node : vertices) {
        delete node;
    }
}

template <typename T>
void Graph<T>::matrixToGraph(std::vector<std::vector<T>> m) {
    adjList.clear();
    for(int i = 0; i < m.size(); i++) { addNode(i); }

    for(int i = 0; i < m.size(); i++) {
        for(int j = 0; j < m[i].size(); j++) {
            if(m[i][j]) { // edge exists
                addEdge(i, j);
            }
        }
    }
}

template <typename T>
void Graph<T>::addNode(T val) {
    Node<T>* newNode = new Node<T>(val);
    vertices.push_back(newNode);
    adjList.push_back(std::unordered_map<int,int>());
}

template <typename T>
Node<T>* Graph<T>::getNode(int id) {
    return vertices[id];
}

// if v or w don't exist in the adjacency list, returns false
// otherwise, creates an edge between two existing nodes, returns true
template <typename T>
bool Graph<T>::addEdge(int v, int w, int weight) {
    if ((v >= adjList.size() || w >= adjList.size())
         || (v < 0 || w < 0)) { return false; }

    // if the same, we assume edge weight 0
    if (v == w) { return false; }

    adjList[v][w] = weight;

    if (!isDirected && v != w) {
        adjList[w][v] = weight;
    }
    return true;
}

template <typename T>
bool Graph<T>::remEdge(int v, int w) {
    return false;
}

template <typename T>
void Graph<T>::printAdjList() {
    for (int i = 0; i < adjList.size(); ++i) {
        std::cout << "Adjacency list for vertex " << i << " (" << vertices[i]->getData() << "): ";

        for (const auto& pair : adjList[i]) {
            int neighbor = pair.first;
            int weight = pair.second;

            std::cout << vertices[neighbor]->getData() << "(" << neighbor << ", " << weight << ") ";
        }

        std::cout << std::endl;
    }
}

// algos:


// breadth first search
// returns order of vertex ids in bfs
template <typename T>
std::vector<int> Graph<T>::bfs(int s) {
    std::vector<int> bfs_order{};
    std::vector<bool> visited(vertices.size(), false);
    std::queue<int> q{};
    q.push(s);
    return _bfs(visited, q, bfs_order);
}

// recursive for the hell of it
template <typename T>
std::vector<int> Graph<T>::_bfs(std::vector<bool> &visited, std::queue<int> &q, std::vector<int>& bfs_list) {
    if (q.empty()) {
        return bfs_list; // done
    } else {
        int v {q.front()};
        q.pop();

        visited[v] = true;
        bfs_list.push_back(v);

        for(auto it = adjList[v].begin(); it != adjList[v].end(); it++) {
            if (!visited[it->first]) {
                q.push(it->first);  
                visited[it->first] = true;
            }       
        }
    }

    return _bfs(visited, q, bfs_list);
}

template <typename T>
std::vector<int> Graph<T>:: augmented_bfs(int s) {
    std::vector<int> dist(vertices.size(), INT_MAX);
    std::vector<bool> visited(vertices.size(), false);
    std::queue<int> q{};
    q.push(s);
    dist[s] = 0;
    return _augmented_bfs(visited, q, dist);
}

template <typename T>
std::vector<int> Graph<T>::_augmented_bfs( std::vector<bool>& visited,
                                 std::queue<int>& q,
                                 std::vector<int>& dists ) {
    if (q.empty()) {
        return dists; // done
    } else {
        int v {q.front()};
        q.pop();

        visited[v] = true;
        for(auto it = adjList[v].begin(); it != adjList[v].end(); it++) {
            if (!visited[it->first]) {
                q.push(it->first);  
                visited[it->first] = true;
                dists[it->first] = dists[v] + 1;
            }       
        }
    }

    return _augmented_bfs(visited, q, dists);
}

template <typename T>
std::vector<int> Graph<T>::UCC() {
    std::vector<int> cc(vertices.size(), 0);
    std::vector<bool> visited(vertices.size(), false);
    int currCC{0};

    for(int i = 0; i < vertices.size(); i++) {
        if (!visited[i]){
            std::queue<int> q{};
            q.push(i);
            visited[i] = true;
            currCC++;

            while (!q.empty()) {
                int v {q.front()};
                q.pop();
                visited[v] = true;
                cc[v] = currCC;
                for(auto it = adjList[v].begin(); it != adjList[v].end(); it++) {
                    if (!visited[it->first]) {
                        q.push(it->first);  
                        visited[it->first] = true;
                    }       
                }
            }
        }
    }
    return cc;
}

// depth first search
// returns order of vertex ids in dfs
template <typename T>
std::vector<int> Graph<T>::dfs(int s) {
    // done iteratively to switch things up
    std::vector<int> dfs_order{};
    std::vector<bool> visited(vertices.size(), false);
    std::stack<int> stack;
    stack.push(s);

    while(!stack.empty()) {
        int v {stack.top()};
        stack.pop();
        
        visited[v] = true;
        dfs_order.push_back(v);

        for(auto it = adjList[v].begin(); it != adjList[v].end(); it++) {
            if (!visited[it->first]) {
                stack.push(it->first);
                visited[it->first] = true;
            }       
        }
    }

    return dfs_order;
}

// returns vertices in topological ordering where index refers to order, toposort[index] refers to vertex
// ONLY works for directed **acyclic** graphs
// otherwise, there is no topological ordering and should throw an exception
template <typename T>
std::vector<int> Graph<T>::toposort() {
    std::vector<bool> visited(vertices.size(),false);
    std::vector<int> labels(vertices.size(), -1);

    int currLabel = vertices.size() - 1;
    for (int i = 0; i < vertices.size(); i++) {
        if(!visited[i]) {
            _toposort(visited, labels, currLabel, i);
        }
    }

    return labels;
}

template <typename T>
std::vector<int> Graph<T>::_toposort(std::vector<bool>& visited, std::vector<int>& labels, int& currLabel, int s) {
    visited[s] = true;
    for(auto it = adjList[s].begin(); it != adjList[s].end(); it++) {
        if (!visited[it->first]) {
            visited[it->first] = true;
            _toposort(visited, labels, currLabel, it->first);
        }
    }
    labels[currLabel--] = s;
    return labels;
}

// // returns SCCs with their vector indices contained in them
template <typename T>
std::vector<int> Graph<T>::kosaraju() {
    Graph<T> rev = reversedGraph();
    std::vector<bool> visited(vertices.size(), false);
    std::vector<int> sccgroups(vertices.size(), -1);
    // toposort on rev to find order (increasing) to start @ sink SCC node
    std::vector<int> orderExtractedFromRev = rev.toposort();
    int numSCCs{0};

    for (int v : orderExtractedFromRev) {
        if(!visited[v]) {
            numSCCs++; // min val = 1
            dfs_scc(visited, sccgroups, numSCCs, v);
        }
    }
    return sccgroups;
}

template <typename T>
std::vector<int> Graph<T>::dfs_scc(std::vector<bool>& visited, std::vector<int>& SCCgroups, int& currSCC, int v) {
    visited[v] = true;
    SCCgroups[v] = currSCC;
    for(auto it = adjList[v].begin(); it != adjList[v].end(); it++) {
        if (!visited[it->first]) {
            visited[it->first] = true;
            SCCgroups = dfs_scc(visited, SCCgroups, currSCC, it->first);
        }
    }

    return SCCgroups;
}

template <typename T>
Graph<T> Graph<T>::reversedGraph() {
    // brute force "create new graph"
    Graph<T> rev(isDirected, isWeighted);

    for (int i = 0; i < vertices.size(); ++i) {
        rev.addNode(vertices[i]->getData());
    }

    for (int i = 0; i < adjList.size(); ++i) {
        for (const auto& pair : adjList[i]) {
            int neighbor = pair.first;
            int weight = pair.second;

            rev.addEdge(neighbor, i, weight);
        }
    }
    return rev;
}


// returns shortest path from some vertex s
template <typename T>
std::vector<int> Graph<T>::dijkstra(int s) {
    std::vector<int> lens(vertices.size(), INT_MAX);                  // results; unconnected vertices will not be processed
    std::unordered_set<int> set{};                                    // lookup vertices in X 
    std::vector<std::tuple<int,int>> localEdges{};
    bool edgesLeft{true};

    lens[s] = 0;
    set.insert(s);
    
    int v = s;
    while(true) {

        for(auto it = adjList[v].begin(); it != adjList[v].end(); it++) {
            if (set.find(it->first) == set.end()) { // not processed in X yet
                // set up d-score list
                localEdges.push_back(std::make_tuple(it->first, lens[v] + it->second));
            }
        }

        // find smallest, include w* into X, remove/ignore other d-score edges pointing to w*
        // this is where we add heap
        int minScoreVertex{-1};
        int minScore{INT_MAX};

        for(int i = 0; i < localEdges.size(); i++) {
            // ignore those not in X (very inefficent)
            if(set.find(std::get<0>(localEdges[i])) == set.end() && std::get<1>(localEdges[i]) < minScore) {
                minScore = std::get<1>(localEdges[i]);
                minScoreVertex = std::get<0>(localEdges[i]);

            }
        }

        if (minScoreVertex < 0) {
            break;
        }

        lens[minScoreVertex] = minScore;
        set.insert(minScoreVertex); // add into set X
        // if(indexToRemove > -1)
        // // localEdges.erase(localEdges.begin() + indexToRemove); // erase from localEdges
        v = minScoreVertex;
    }

    return lens;
}

#endif