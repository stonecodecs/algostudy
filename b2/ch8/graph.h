#ifndef GRAPH_H
#define GRAPH_H

#include"node.h"
#include<tuple>
#include<limits.h>
#include<unordered_map>
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
    public:
        Graph(bool directed=false, bool weighted=false);
        ~Graph();
        void addNode(T val);
        Node<T>* getNode(int id);
        bool addEdge(int v, int w, int weight=1);
        bool remEdge(int v, int w);
        void printAdjList();

        // algos:
        std::vector<int> bfs(int s);
        std::vector<int> augmented_bfs(int s);
        std::vector<int> UCC(); // connected components
        std::vector<int> dfs(int s);
        std::vector<std::vector<int>> kosaraju();
        std::vector<std::tuple<int,int>> dijkstra();
        std::vector<std::tuple<int,int>> dijkstra_primitive();
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

// returns SCCs with their vector indices contained in them
// std::vector<std::vector<int>> kosaraju() {

// }

// // 
// std::vector<std::tuple<int,int>> dijkstra_primitive() {

// }

// std::vector<std::tuple<int,int>> dijkstra() {

// }


#endif