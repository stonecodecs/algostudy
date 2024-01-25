#include "graph.h"
#include "heap.h"
#include "node.h"
#include <string>
#include "gtest/gtest.h"

#define GTEST_ENABLED

template <typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "[ ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << "]" << std::endl;
}

template <typename T>
void print2DVector(const std::vector<T>& vec) {
    std::cout << "[ \n";
    for (const auto& row : vec) {
        std::cout << "\t[ ";
        for (const auto& col : row) {
            std::cout << col << " ";
        }
        std::cout << "],\n";
    }
    std::cout << "]" << std::endl;
}

#ifdef GTEST_ENABLED

TEST(HeapTests, HeapInsert) {
    std::vector<char> initialOrder = {'a', 'b', 'd', 'e', 'c'};
    Heap<char*> a_heap = Heap<char*>::heapify({
        std::make_tuple(2, &initialOrder[0]),
        std::make_tuple(8, &initialOrder[1]),
        std::make_tuple(3, &initialOrder[2]),
        std::make_tuple(4, &initialOrder[3]),
        std::make_tuple(1, &initialOrder[4])
    });

    std::tuple<int, char*> top{};
    std::vector<char> correctOrder = {'c', 'a', 'd', 'e', 'b'};

    for(int i = 0; i < a_heap.size(); i++) {
        top = a_heap.extractTop();
        EXPECT_EQ(correctOrder[i], *(std::get<1>(top)));
    }
}

TEST(HeapTests, HeapRemove) {
    std::vector<char> initialOrder = {'a', 'b', 'd', 'e', 'c'};
    Heap<char*> a_heap = Heap<char*>::heapify({
        std::make_tuple(2, &initialOrder[0]),
        std::make_tuple(8, &initialOrder[1]),
        std::make_tuple(3, &initialOrder[2]),
        std::make_tuple(4, &initialOrder[3]),
        std::make_tuple(1, &initialOrder[4])
    });

    std::tuple<int, char*> top{};
    std::vector<char> correctOrder = {'c', 'b'};
    a_heap.remove(&initialOrder[0]);
    a_heap.remove(&initialOrder[2]);
    a_heap.remove(&initialOrder[3]);
    for(int i = 0; i < a_heap.size(); i++) {
        top = a_heap.extractTop();
        EXPECT_EQ(correctOrder[i], *(std::get<1>(top)));    // warning: arbitrary order (may be [c,b] or [b,c])
    }
}

TEST(GraphTests, DijkstraTest) {
    Graph<char> djk_g(true, true);
    std::vector<int> expected0 {0,1,3,6};
    std::vector<int> expected1 {INT_MAX,0,2,5};
    djk_g.addNode('s');
    djk_g.addNode('v');
    djk_g.addNode('w');
    djk_g.addNode('t');

    djk_g.addEdge(0, 1, 1);
    djk_g.addEdge(0, 2, 4);
    djk_g.addEdge(1, 2, 2);
    djk_g.addEdge(1, 3, 6);
    djk_g.addEdge(2, 3, 3);

    ASSERT_EQ(expected0, djk_g.dijkstra(0));
    ASSERT_EQ(expected1, djk_g.dijkstra(1));


}


#endif

int main(int argc, char** argv) {
#ifndef GTEST_ENABLED
    // Graph<char> undirected_g = Graph<char>();
    // Graph<char> directed_g   = Graph<char>(true);

    // //simulating example 8.4.1
    // undirected_g.addNode('s');
    // for (int i = 0; i < 5; i++) {
    //     undirected_g.addNode(97+i); // 97 is 'a' in ascii
    // }

    // undirected_g.addEdge(0, 1); // s->a
    // undirected_g.addEdge(0, 2); // s->b
    // undirected_g.addEdge(1, 3); // a->c
    // undirected_g.addEdge(2, 3); // b->c
    // undirected_g.addEdge(2, 4); // b->d
    // undirected_g.addEdge(3, 4); // c->d
    // undirected_g.addEdge(3, 5); // c->e
    // undirected_g.addEdge(4, 5); // d->e
    
    // undirected_g.printAdjList();

    // std::vector<int> orderOfBFS = undirected_g.bfs(0);
    // printVector(orderOfBFS);

    // std::vector<int> distsFromAugmentedBFS = undirected_g.augmented_bfs(0);
    // printVector(distsFromAugmentedBFS);

    // std::vector<int> orderOfDFS = undirected_g.dfs(0);
    // printVector(orderOfDFS);

    // undirected_g.addNode('f'); // vert6
    // undirected_g.addNode('g'); // vert7
    // undirected_g.addEdge(6,7);

    // undirected_g.printAdjList();

    // printVector(undirected_g.UCC());

    // // directed
    // for (int i = 0; i < 4; i++) {
    //     directed_g.addNode(97+i); // 97 is 'a' in ascii
    // }

    // directed_g.addEdge(0, 2);
    // directed_g.addEdge(0, 1);
    // directed_g.addEdge(2, 3);
    // directed_g.addEdge(1, 3);

    // directed_g.printAdjList();
    // printVector(directed_g.toposort());

    // // reproduce example from 8.16, except with an island node (index 0)
    // std::vector<std::vector<int>> test{
    //                                     {0,0,0,0,0,0,0,0,0, 0, 0, 0}, // 0-> [island]
    //                                     {0,0,0,1,0,0,0,0,0, 0, 0, 0}, // 1->3
    //                                     {0,0,0,0,1,0,0,0,0, 0, 1, 0}, // 2->4,10
    //                                     {0,0,0,0,0,1,0,0,0, 0, 0, 1}, // 3->5,11
    //                                     {0,0,0,0,0,0,0,1,0, 0, 0, 0}, // 4->7
    //                                     {0,1,0,0,0,0,0,1,0, 1, 0, 0}, // 5->1,7,9
    //                                     {0,0,0,0,0,0,0,0,0, 0, 1, 0}, // 6->10
    //                                     {0,0,0,0,0,0,0,0,0, 1, 0, 0}, // 7->9
    //                                     {0,0,0,0,0,0,1,0,0, 0, 0, 0}, // 8->6
    //                                     {0,0,1,0,1,0,0,0,1, 0, 0, 0}, // 9->2,4,8
    //                                     {0,0,0,0,0,0,0,0,1, 0, 0, 0}, // 10->8
    //                                     {0,0,0,0,0,0,1,0,1, 0, 0, 0}, // 11->6,8                                                                                                                                                                                         
    //                                   };
    // Graph<int> dg_forSCCs = Graph<int>(true, false);
    // dg_forSCCs.matrixToGraph(test);
    // print2DVector(test);

    Graph<char> djk_g(true, true);
    djk_g.addNode('s');
    djk_g.addNode('v');
    djk_g.addNode('w');
    djk_g.addNode('t');

    djk_g.addEdge(0, 1, 1);
    djk_g.addEdge(0, 2, 4);
    djk_g.addEdge(1, 2, 2);
    djk_g.addEdge(1, 3, 6);
    djk_g.addEdge(2, 3, 3);

    djk_g.printAdjList();

    printVector(djk_g.dijkstra(0));
    return 0;

#endif

#ifdef GTEST_ENABLED
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}