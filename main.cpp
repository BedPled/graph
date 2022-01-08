#include <iostream>
#include "graph.h"
int main() {

    graph a;

    a.addNode(5);
    a.addNode(1);
    a.addNode(3);
    a.addNode(6);
    a.addNode(4);

    a.addArc(5,6,5);
    a.addArc(1,3,4);
    a.addArc(5,1,5);
    a.addArc(3,5,8);
    a.addArc(5,5,2);
    a.addArc(4,5,4);
    a.addArc(4,1,8);
    a.addArc(4,3,5);
    a.addArc(4,6,9);

    a.addArc(5,4, 3);
    a.addArc(1,4, 6);
    a.addArc(3,4, 8);
    a.addArc(4,4, 7);

//    std::cout << "------------------------------------------------------------" << std::endl;
//    a.print();
//    std::cout << "------------------------------------------------------------" << std::endl;


    a.DIJKSTRA();

    std::cout << "------------------------------------------------------------" << std::endl;
    a.print();
    std::cout << "------------------------------------------------------------" << std::endl;



    std::cout << "Hello, World!" << std::endl;
    return 0;
}


