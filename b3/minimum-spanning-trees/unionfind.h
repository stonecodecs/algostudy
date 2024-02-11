#ifndef UNION_FIND
#define UNION_FIND
#include<iostream>
#include<vector>
#include<unordered_map>

template<typename T>
class UnionFind {
private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, int> rank;

public:
    UnionFind();
    T find(const T& x);
    void unionSets(const T& x, const T& y);
    bool sameSet(const T& x, const T& y);
};

template<typename T>
UnionFind<T>::UnionFind() {}

    // Find operation with path compression
template<typename T>
T UnionFind<T>::find(const T& x) {
    if (parent.find(x) == parent.end()) { // if not found, create entry...? init step
        parent[x] = x;
        rank[x] = 0;
    }
    if (parent[x] != x) { 
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

// Union operation by rank
template<typename T>
void UnionFind<T>::unionSets(const T& x, const T& y) {
    T rootX = find(x);
    T rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// Check if two elements are in the same set
template<typename T>
bool UnionFind<T>::sameSet(const T& x, const T& y) {
    return find(x) == find(y);
}



#endif