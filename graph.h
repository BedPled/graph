//
// Created by pledushka on 06.01.2022.
//
#include <iostream>
#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
struct node;
struct arc;

struct node { // вершина графа

    int number; // номер вершины
    node* nextNode; // следующая вершина
    arc* arcs; // ссылка на список дуг

    // для дейкстры
    int d = INT16_MAX;
    node *p = nullptr;

    node() {
        nextNode = nullptr;
        arcs = nullptr;
    }
};

struct arc { // дуга графа
    node* node_; // ссылка на вершину, в которую смотрит дуга
    arc* next; // ссылка на следующую вершину
    int weight;

    arc() {
        weight = 0;
        node_ = nullptr;
        next = nullptr;
    }

};

class graph {
    node *root;
public:

    // Конструктор
    graph() {
        root = nullptr;
    }

    graph(int a) {
        root = new node();
        root->number = a;
    }

    //Деструктор
    ~graph() {
        node *help;
        while (root != nullptr) {
            help = root->nextNode;
            delNode(root->number);
            root = help;
        }
        root = nullptr;
    }

    //Добавление вершины
    int addNode (int a) {
        if (root == nullptr) {
            root = new node;
            root->number = a;
            return true;
        } else {
            // поиск ноды с таким же номером (вдруг уже существует)
            node *cur = root;

            if (cur->number > a) {
                // добавление новой ноды в начало
                root = new node;
                root->number = a;
                root->nextNode = cur;
                return true;
            } else if (cur->number == a) {
                return false;
            }

            while (cur->nextNode != nullptr) {
                if (cur->nextNode->number > a) {
                    // добавление новой ноды в середину (упорядочено)
                    node *newNode = new node;
                    newNode->number = a;
                    newNode->nextNode = cur->nextNode;
                    cur->nextNode = newNode;
                    return true;
                } else if (cur->nextNode->number == a) {
                    return false;
                }
                cur = cur->nextNode;
            }

            // добавление ноды в конец
            node *newNode = new node;
            newNode->number = a;
            cur->nextNode = newNode;
            return true;

        }
    }

    //Добавление дуги
    int addArc (int a, int b, int w = 1) { // а - откуда b - куда
        // ищем дугу

        node *nodeA = root;
        node *nodeB = root;

        while (nodeA != nullptr && nodeA->number != a) {
            nodeA = nodeA->nextNode;
        }
        while (nodeB != nullptr && nodeB->number != b) {
            nodeB = nodeB->nextNode;
        }

        if (nodeA == nullptr) {
            std::cout << "node "<< a <<" not found" << std::endl;
            return false;
        }
        if (nodeB == nullptr) {
            std::cout << "node " << b << " not found" << std::endl;
            return false;
        }

        if (nodeA->number == a && nodeB->number == b) {
            // проверка на то что дуги нет
            // ищем куда добавить

            //---------------------------------

            if (nodeA->arcs == nullptr) { // не существует дуг
                nodeA->arcs = new arc;
                nodeA->arcs->node_ = nodeB;
                nodeA->arcs->weight = w;
                return true;
            } else { // существует хотя бы одна дуга
                // поиск дуги с таким же номером (вдруг уже существует)
                arc *curArc = nodeA->arcs; // node *cur = root; (было)

                if (curArc->node_->number > b  /*cur->number > a*/) {
                    // добавление новой дуги в начало
                    nodeA->arcs = new arc;
                    nodeA->arcs->node_ = nodeB;
                    nodeA->arcs->next = curArc;
                    nodeA->arcs->weight = w;
                    return true;
                } else if (curArc->node_->number == b) {
                    return false;
                }

                while (curArc->next != nullptr  /*cur->nextNode != nullptr*/) {
                    if (curArc->next->node_->number > b /*cur->nextNode->number > a*/) {
                        // добавление новой ноды в середину (упорядочено)
                        arc *newArc = new arc; //node *newNode = new node;
                        newArc->node_ = nodeB; //newNode->number = a;
                        newArc->next = curArc->next; //newNode->nextNode = cur->nextNode;
                        newArc->weight = w;
                        curArc->next = newArc; //cur->nextNode = newNode;

                        return true;
                    } else if (curArc->next->node_->number == b /*cur->number == a*/) {
                        return false;
                    }
                    curArc = curArc->next;
                }

                // добавление ноды в конец
                arc *newArc = new arc; //node *newNode = new node;
                newArc->node_ = nodeB; //newNode->number = a;
                newArc->weight = w;
                curArc->next = newArc; //cur->nextNode = newNode;
                return true;
            }
            //---------------------------------

            // создаём новую дугу

            // добавляем дугу
        }
        std::cout << "ВСЁ ОЧЕНЬ ПЛОХО!!!";
        return false;
    }

    //Удаление вершины
    int delNode (int a) {
    // существует ли вершина?
        node *nodeA = root;
        node *nodeHelp = nullptr;

        while (nodeA != nullptr && nodeA->number != a) {
            nodeHelp = nodeA;
            nodeA = nodeA->nextNode;
        }

        if (nodeA == nullptr) {
            std::cout << "node "<< a <<" not found" << std::endl;
            return false;
        }

        // идём по всем вершинам и ищем вхождение вершины в дугах. Удаляем эти дуги
        node *curNode = root;
        arc *curArc;
        arc *helpArc;

        while (curNode != nullptr) {
            curArc = curNode->arcs;

            if (curArc != nullptr) {
                while (curArc != nullptr) {
                    helpArc = curArc;
                    curArc = curArc->next;
                    if (helpArc->node_ == nodeA) {
                        delArc(curNode->number, a); // храни господь эту строчку
                    }
                }
            }

            curNode = curNode->nextNode;
        }

        // удаляем все дуги выходящие из вершины А
        curArc = nodeA->arcs;
        arc *curArcHelp;

        while (curArc != nullptr) {
            curArcHelp = curArc;
            curArc = curArc->next;
            delete curArcHelp;
        }

        // удаляем вершину A
        if (nodeHelp == nullptr) { // А - первая вершина списка
            root = nodeA->nextNode;
        } else if (nodeA->nextNode == nullptr){ // А - последняя вершина списка
            nodeHelp->nextNode = nullptr;
        } else { // А - вершина в середине
            nodeHelp->nextNode = nodeA->nextNode;
        }
        delete nodeA;
        return true;
    }

    //Удаление дуги
    int delArc (int a, int b) {
        node *nodeA = root;
        node *nodeB = root;

        while (nodeA != nullptr && nodeA->number != a) {
            nodeA = nodeA->nextNode;
        }
        while (nodeB != nullptr && nodeB->number != b) {
            nodeB = nodeB->nextNode;
        }

        if (nodeA == nullptr) {
            std::cout << "node "<< a <<" not found" << std::endl;
            return false;
        }
        if (nodeB == nullptr) {
            std::cout << "node " << b << " not found" << std::endl;
            return false;
        }

        arc *curArc = nodeA->arcs;
        arc *lastArc = nullptr;

        while (curArc != nullptr && curArc->node_ != nodeB) { // ищем дугу
            lastArc = curArc;
            curArc = curArc->next;
        }

        if (curArc->node_ == nodeB) {
            if (lastArc == nullptr) { // АB - первая дуга
                lastArc = curArc->next;
                nodeA->arcs = lastArc;
            } else if (curArc->next == nullptr) { // АB - последняя дуга списка
                lastArc->next = nullptr;
            } else { // А - вершина в середине
                lastArc->next = curArc->next;
            }
            delete curArc;
            return true;

        } else return false;

    }

    //Поиск вершины
    int searchNode(int a){
        node *nodeA = root;

        while (nodeA != nullptr && nodeA->number != a) {
            nodeA = nodeA->nextNode;
        }

        if (nodeA == nullptr) {
            std::cout << "node "<< a <<" not found" << std::endl;
            return false;
        } else return true;
    }

    //Поиск дуги
    int searchArc(int a, int b){
        node *nodeA = root;
        node *nodeB = root;

        while (nodeA != nullptr && nodeA->number != a) {
            nodeA = nodeA->nextNode;
        }
        while (nodeB != nullptr && nodeB->number != b) {
            nodeB = nodeB->nextNode;
        }

        if (nodeA == nullptr) {
            std::cout << "node "<< a <<" not found" << std::endl;
            return false;
        }
        if (nodeB == nullptr) {
            std::cout << "node " << b << " not found" << std::endl;
            return false;
        }

        arc *curArc = nodeA->arcs;

        while (curArc != nullptr && curArc->node_ != nodeB) { // ищем дугу
            curArc = curArc->next;
        }

        if (curArc != nullptr && curArc->node_ == nodeB) {
            return true;
        } else return false;
    }
    //Печать графа
    void print(){
        node *thisNode = root;
        arc *thisArc;

        if (thisNode == nullptr) {
            std::cout << "graph is empty" << std::endl;
        } else {
            while (thisNode != nullptr) {
                std::cout << "|" << thisNode->number << "| D(" << thisNode->p << ") | -> ";
                thisArc = thisNode->arcs;

                while (thisArc != nullptr) {
                    std::cout << thisArc->node_->number << "("<< thisArc->weight <<")" << " -> ";
                    thisArc = thisArc->next;
                }
                std::cout << " \\ " << std::endl;
                thisNode = thisNode->nextNode;
            }
        }
    };

    //Обход ()


    //Алгоритм ()


    // дейкстра

    void ISS (node *s) {
        node *curNode = root;

        while (curNode != nullptr) {
            curNode->d = INT16_MAX;
            curNode->p = nullptr;
            curNode = curNode->nextNode;
        }

        s->d = 0;
    }

    void relax (node *u, node *v, int w) {
        if (v->d >= u->d + w) {
            v->d = u->d + w;
            v->p = u;
        }
    }

    int countNode(){
        node *curNode = root;
        int count = 0;

        while (curNode != nullptr) {
            count++;
            curNode = curNode->nextNode;
        }
        return count;
    }

    void DIJKSTRA() {
        int count = countNode();
        int countQ = count;
        int countS = 0;
        node **S = new node* [count];
        node **Q = new node* [count];
        node *curNode = root;
        node *u = nullptr;
        node *v = nullptr;

        for (int i = 0; i < count; ++i) {
            Q[i] = curNode;
            curNode = curNode->nextNode;
        }



        while (countQ != 0) {
            u = Q[countQ-1];
            countQ--;

            S[countS] = u;
            countS++;

            v = root;
            for (int i = 0; i < count - 1; ++i) {

                // поиск ребра

                node *nodeA = root;
                node *nodeB = root;
                int a = u->number;
                int b = v->number;
                bool pupalupa = true;

                while (nodeA != nullptr && nodeA->number != a) {
                    nodeA = nodeA->nextNode;
                }
                while (nodeB != nullptr && nodeB->number != b) {
                    nodeB = nodeB->nextNode;
                }

                if (nodeA == nullptr) {
                    std::cout << "node "<< a <<" not found" << std::endl;
                    pupalupa =  false;
                }
                if (nodeB == nullptr) {
                    std::cout << "node " << b << " not found" << std::endl;
                    pupalupa =  false;
                }

                arc *curArc = nodeA->arcs;
                arc *lastArc = nullptr;

                while (curArc != nullptr && curArc->node_ != nodeB) { // ищем дугу
                    lastArc = curArc;
                    curArc = curArc->next;
                }

                if (curArc == nullptr) pupalupa = false;

                if (pupalupa && curArc->node_ == nodeB) {
                    relax(u, v, curArc->weight);
                }
            }

        }

    };


};


#endif //GRAPH_GRAPH_H
