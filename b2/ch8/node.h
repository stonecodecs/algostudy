#ifndef NODE_H
#define NODE_H

#include<vector>
#include<iostream>

// BIG: Templates can only run on headerfiles

template <typename T>
class Node {
    private:
        static int nodeCountTotal;
        int uid;
        T data;
    public:
        Node(T value);
        ~Node();
        static int getNodeCount();
        int getID();
        T getData();
        

};

template<typename T>
int Node<T>::nodeCountTotal = 0;

template <typename T>
Node<T>::Node(T value) : data(value) {
    uid = nodeCountTotal;
    nodeCountTotal++;
}

template <typename T>
Node<T>::~Node() {
    
}

template <typename T>
int Node<T>::getID() {
    return uid;
}

template <typename T>
T Node<T>::getData() {
    return data;
}

template <typename T>
int Node<T>::getNodeCount() {
    return nodeCountTotal;
}

#endif