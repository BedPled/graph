#include <iostream>
#include "graph.h"

int main() {

    graph a;


    for (int i = 1; i < 10; i++)
        a.addNode(10 - i);

    for (int i = 1; i < 10; i++)
        for (int j = 1; j < 10; j++) {
    a.addArc(i, i+1, -1);
          //  a.addArc(i+j, j, i-j);

}
    a.addArc(9, 1, 3);
    a.delArc(5, 6);
    a.addArc(5, 6, 6);

graph b;

    for (int i = 1; i <= 10; ++i) {
        b.addNode(i);
    }

    b.addArc(1,9,1);
    b.addArc(1,4,-5);
    b.addArc(2,9,2);
    b.addArc(2,7,1);
    b.addArc(3,8,1);
    b.addArc(3,5,10);
    b.addArc(4,7,-2);
    b.addArc(4,10,4);
    b.addArc(5,10,3);
    b.addArc(6,10,1);
    b.addArc(7,1,5);
    b.addArc(7,6,1);
    b.addArc(8,5,8);
    b.addArc(8,2,1);
    b.addArc(8,6,4);
    b.addArc(9,3,1);

//    for (int i = 0; i < 7; ++i) {
//        for (int j = i; j < 7; ++j) {
//            b.addArc(j, i, 0);
//        }
//    }
//    b.addArc(1,6,4);


    std::cout << "------------------------------------------------------------" << std::endl;
//    a.print();
    b.print();
    std::cout << "------------------------------------------------------------" << std::endl;

//    std::cout << a.bellmanFord(1) << std::endl;
    std::cout << b.bellmanFord(1) << std::endl;
//b.DIJKSTRA(1);
    std::cout << "------------------------------------------------------------" << std::endl;
//    a.print();
    b.print();
    std::cout << "------------------------------------------------------------" << std::endl;


    std::cout << "End" << std::endl;
    return 0;
}




