#ifndef HEAP_H
#define HEAP_H

#include<vector>
#include<iostream>
#include<unordered_map>
#include<unordered_set>

template <typename T>
class Heap {
    private:
        std::vector<std::tuple<int, T>> heap;       // <key, object>
        std::unordered_map<int, std::unordered_set<int>> keyIndexMap;   // <key, index>
        bool minHeap; // true==minHeap, false==maxHeap
        int bubbleDown(int s);
        int bubbleUp(int s);
        int indexAfterRangeCheck(int s); // -1 if not in range
        int getParentIndex(int s);
        int getLchild(int s);
        int getRchild(int s);
        bool swap(int a, int b);
        int getKey(std::tuple<int, T> a);
        T getObj(std::tuple<int, T> a);
    public:
        Heap(bool minHeap=true);
        T extractTop();
        T findTop();
        void insert(std::tuple<int, T> a);
        void insert(int key, T object);
        void remove(int a);
        static Heap<T> heapify(const std::vector<std::tuple<int, T>>& input, bool minHeap=true);
        bool isEmpty();
        int size();
        void printHeap();
        void printHash();
};

template <typename T>
Heap<T>::Heap(bool minHeap) : heap(std::vector<std::tuple<int,T>>()),
                              minHeap(minHeap),
                              keyIndexMap(std::unordered_map<int, std::unordered_set<int>>()) {}

template <typename T>
bool Heap<T>::isEmpty() { return (heap.size() > 0) ? false : true; }

template <typename T>
int  Heap<T>::size() { return heap.size(); }

template <typename T>
int Heap<T>::indexAfterRangeCheck(int s) {
    return (s < size() && s >= 0) ? s : -1;
}

template <typename T>
int  Heap<T>::getParentIndex(int s) { return indexAfterRangeCheck((s-1)/2); }

template <typename T>
int  Heap<T>::getLchild(int s) { return indexAfterRangeCheck((s+1)*2 - 1); }

template <typename T>
int  Heap<T>::getRchild(int s) { return indexAfterRangeCheck((s+1)*2); }

template <typename T>
int Heap<T>::getKey(std::tuple<int, T> a) {
    return std::get<0>(a);
}

template <typename T>
T Heap<T>::getObj(std::tuple<int, T> a){
     return std::get<1>(a);
}

template <typename T>
bool Heap<T>::swap(int a, int b) { // a and b being indices
    int n = size();
    if (a > n || b > n || a < 0 || b < 0) { return false; }

    // swap indices in hashset in overall hashmap
    int key_a{getKey(heap[a])};
    int key_b{getKey(heap[b])};
    keyIndexMap[key_a].erase(a);
    keyIndexMap[key_b].erase(b);
    keyIndexMap[key_a].insert(b);
    keyIndexMap[key_b].insert(a);

    // swap actual tuples
    std::tuple<int, T> temp {heap[a]};
    heap[a] = heap[b];
    heap[b] = temp;
    return true;
}

template <typename T>
T Heap<T>::extractTop() {
    if (isEmpty()) { throw std::runtime_error("Heap is empty. Cannot extract."); }
    T top{findTop()};
    remove(getKey(heap[0]));
    return top;
}

template <typename T>
T Heap<T>::findTop() {
    if (isEmpty()) { throw std::runtime_error("Heap is empty."); }
    return getObj(heap[0]);
}

template <typename T>
void Heap<T>::insert(std::tuple<int, T> a) { 
    heap.push_back(a);
    int last {size() - 1}; 
    keyIndexMap[getKey(a)].insert(last);
    if (last > 0) {
        bubbleUp(last); // restore
    }
}

template <typename T>
void Heap<T>::insert(int key, T obj) {
    insert(std::tuple<int,T>(key, obj));
}

// remove by key: use hash table
template <typename T>
void Heap<T>::remove(int key) {
    int last {size() - 1};
    if(last < 0) { return; }
    if(keyIndexMap[key].empty()) { return; }

    // get first index that corresponds to "key"
    int indexToRemove{-1};
    auto it = keyIndexMap[key].begin();
    if(it != keyIndexMap[key].end()) {
        indexToRemove = *it;
    }

    // swap with index
    swap(indexToRemove, last);
    heap.erase(heap.begin() + last);
    keyIndexMap[key].erase(last);
    bubbleDown(indexToRemove); // restore 
}

template <typename T>
Heap<T> Heap<T>::heapify(const std::vector<std::tuple<int, T>>& input, bool minHeap) {
    Heap<T> result(minHeap);
    for(int i = 0; i < input.size(); i++) { 
        std::tuple<int, T> newNode(input[i]);
        result.insert(newNode);
    }
    return result;
}

template <typename T>
int Heap<T>::bubbleDown(int s) { // s is index
    int left{0};
    int right{0};
    int curr{s};
    // while still traversals
    while(indexAfterRangeCheck(curr) >= 0 &&
     (left = getLchild(curr)) >= 0) {
        right = getRchild(curr);

        if (right >= 0) { // will always check RIGHT child first
            if (getKey(heap[right]) <= getKey(heap[left])) {
                swap(curr, right);
                curr = right;
            } else {
                swap(curr, left);
                curr = left;
            }
        } else { // no right child, check left
            if (getKey(heap[curr]) < getKey(heap[left])) {
                break; 
            }
            swap(curr, left);
            curr = left;
        }
    }

    return curr;
}

template <typename T>
int Heap<T>::bubbleUp(int s) { // s is index
    int parent{getParentIndex(s)};
    if(parent == s) { return s; } //implies root
    int curr{s};
    while(parent >= 0) {
        if(getKey(heap[parent]) > getKey(heap[curr])) {
            swap(curr, parent);
            curr = parent;
            parent = getParentIndex(parent);
        } else { return curr; }
    }

    return curr;
}

template <typename T>
void Heap<T>::printHeap() {
    std::cout << "sizeofheap:" << heap.size() << "\n";
    std::cout << "[";
    for(int i = 0; i < size(); i++) {
        std::cout << "(" << getKey(heap[i]) << ": " << getObj(heap[i]) << ") ";
        // may not work for all types T
    }
    std::cout << "]\n";
}

template <typename T>
void Heap<T>::printHash() {
    std::cout << "[";
    for (auto it = keyIndexMap.begin(); it != keyIndexMap.end(); ++it) {
        std::cout << "Key: " << it->first << ", indices: ";
        // Iterate over the unordered_set for the current key
        for (const auto& value : it->second) {
            std::cout << value << " ";
        }

        std::cout << std::endl;
    }
    std::cout << "]\n";
}

#endif
