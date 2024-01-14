#include "graph.h"
#include "node.h"
#include<string>

template <typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "[ ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << "]" << std::endl;
}

int main(int argc, char** argv) {
    Graph<char> g = Graph<char>();

    //simulating example 8.4.1
    g.addNode('s');
    for (int i = 0; i < 5; i++) {
        g.addNode(97+i); // 97 is 'a' in ascii
    }

    g.addEdge(0, 1); // s->a
    g.addEdge(0, 2); // s->b
    g.addEdge(1, 3); // a->c
    g.addEdge(2, 3); // b->c
    g.addEdge(2, 4); // b->d
    g.addEdge(3, 4); // c->d
    g.addEdge(3, 5); // c->e
    g.addEdge(4, 5); // d->e
    
    g.printAdjList();

    std::vector<int> orderOfBFS = g.bfs(0);
    printVector(orderOfBFS);

    std::vector<int> distsFromAugmentedBFS = g.augmented_bfs(0);
    printVector(distsFromAugmentedBFS);

    std::vector<int> orderOfDFS = g.dfs(0);
    printVector(orderOfDFS);

    g.addNode('f'); // vert6
    g.addNode('g'); // vert7
    g.addEdge(6,7);

    g.printAdjList();

    printVector(g.UCC());
    
    return 0;
}