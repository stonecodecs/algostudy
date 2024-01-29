#ifndef NODE_H
#define NODE_H

#include<vector>
#include<iostream>

// BIG: Templates can only run on headerfiles

template <typename T>
class Node {
    private:
        int uid;
        T data;
    public:
        // up to the parent model to maintain unique IDs
        Node(T value, int _id);
        ~Node();
        int getID();
        T getData();
};

template <typename T>
Node<T>::Node(T value, int _id) : data(value), uid(_id) {
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

#endif