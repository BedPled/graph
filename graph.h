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

    // для обхода
    int ND = 0;
    int KD = 0;
//    node *MD = nullptr;

    // для BF
    int d = INT16_MAX;
    node *p = nullptr;

    node() {
        number = -1;
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
                std::cout << "|" << thisNode->number;
                if (thisNode->p == nullptr) std::cout << "undefined";
                else std::cout << thisNode->p->ND;
               std::cout << " | ";

                std::cout << "| D(";
                std::cout << thisNode->d;
                std::cout << ")";

                std::cout << "| BF(";
                if (thisNode->p == nullptr) std::cout << "undefined";
                else std::cout << thisNode->p->number;
                std::cout << ") |";
                std::cout << " -> ";

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

    void ISS (node *s) {
        node *curNode = root;

        while (curNode != nullptr) {
            curNode->d = INT16_MAX;
            curNode->p = nullptr;
            curNode = curNode->nextNode;
        }

        s->d = 0;
    }

    void chill (node *u, arc *a) {
        if (a->node_->d > u->d + a->weight) {
            a->node_->d = u->d + a->weight;
            a->node_->p = u;
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

    int countArc(node *in) {
        arc *curArc = in->arcs;
        int count = 0;

            while (curArc != nullptr) {
                count++;
                curArc = curArc->next;
            }

        return count;
    }

    arc* nodeIndex(node *a, int index) { // возвращаем вершину по индексу. считаем с 1
        arc *curArc = a->arcs;

        for (int i = 1; i <= index; ++i) {
            if (i == index) {
                return curArc;
            }
            curArc = curArc->next;
        }
    }


    void deepFirst(int a) {

        node *qwerty = root;

        while (qwerty != nullptr) {
            qwerty->KD = countArc(qwerty);
            qwerty = qwerty->nextNode;
        }

        node *p = root;

        while (p != nullptr && p->number != a) {
            p = p->nextNode;
        }

        if (p == nullptr) {
            std::cout << "Error! Node is null" << std::endl;
            return;
        }

        node *q0 = new node(); // фиктивная нода
        q0->arcs = new arc();
        q0->arcs->node_ = p;
        q0->KD = 1;
        q0->ND = 0;

        node *t = nullptr; // 1
        node *q = q0; // 2
        q0->ND = 1; // 3
        p = nodeIndex(q, 1)->node_; // 3

        L:

        nodeIndex(q, q->ND)->node_ = t; // 4
        t = q; // 4
        q = p; // 4

        L1:
        if (q != nullptr) {
            while (q->ND < q->KD) { // 6
                if (q->ND == 0) { std::cout << q->number << " - "; }

                q->ND = q->ND + 1; // 7
                p = nodeIndex(q, q->ND)->node_; // следующая достижимая вершина
                if (p != nullptr) {
                    if (p->ND == 0) {
                        goto L;
                    }
                }
            }
        }


        if (p != nullptr) {
            p = q;
            q = t;
            if (q != nullptr) {
                t = nodeIndex(q, q->ND)->node_; // следующая достижимая вершина
                nodeIndex(q, q->ND)->node_ = p;
            }
            goto L1;
        }
    }

    bool bellmanFord(int a) {
        int count = countNode();

        node *curNode = root;

        while (curNode != nullptr && curNode->number != a) {
            curNode = curNode->nextNode;
        }

        if (curNode == nullptr) {
            std::cout << "Error! Node is null" << std::endl;
            return false;
        }

        ISS(curNode);

        arc *helpArc = nullptr;
        node *helpNode = root;

        for (int i = 1; i < count; ++i) {
            helpArc = nullptr;
            helpNode = root;
            while (helpNode != nullptr) { // перебор всех вершин
                helpArc = helpNode->arcs;
                while (helpArc != nullptr) { // перебор всех рёбер
                    chill(helpNode, helpArc);
                    helpArc = helpArc->next;
                }
                helpNode = helpNode->nextNode;
            }
        }

        helpArc = nullptr;
        helpNode = root;

        while (helpNode != nullptr) { // перебор всех вершин
            helpArc = helpNode->arcs;
            while (helpArc != nullptr) {
                if (helpArc->node_->d > helpNode->d + helpArc->weight) {
                    return false;
                }
                helpArc = helpArc->next;
            }
            helpNode = helpNode->nextNode;
        }
        return true;
    }


        bool isEmpty(node *Q[], int count) {
        for (int i = 0; i < count; ++i) {
            if (Q[i] != nullptr) return false;
        }
        return true;
    }

    node *extractMin(node *Q[], int count) {
        node *min_node = new node;
        min_node->d = INT32_MAX;
        int c = -1;

        if(!isEmpty(Q,count)) {
            for (int i = 0; i < count; ++i) {
                if (Q[i] == nullptr) {
                    continue;
                }

                if (Q[i]->d < min_node->d) {
                    min_node = Q[i];
                    c = i;
                }
            }
        }

        Q[c] = nullptr;

        return min_node;
    }

    void DIJKSTRA(int a) {
        int count = countNode();
        //int countQ = count;
        int countS = 0;

        node *S[count];
        node *Q[count];

        node *u = nullptr;

        node *curNode = root;

        while (curNode != nullptr && curNode->number != a) {
            curNode = curNode->nextNode;
        }

        if (curNode == nullptr) {
            std::cout << "Я вас не звал!!!" << std::endl;
            return;
        }

        ISS(curNode);

        node *helpNode = root;

        // инициализация Q и S
        for (int i = 0; i < count; ++i) {
            S[i] = nullptr;
            Q[i] = helpNode;
            helpNode = helpNode->nextNode;
        }

        while (!isEmpty(Q, count)) {
            u = extractMin(Q,count);
            S[countS] = u;
            countS++;

            // для каждого ребра U помечаем вершины как достижимые за определённо расстояние

            // 1. узнать сколько у нас рёбер из U
            //
            arc *curArc = u->arcs;
            while (curArc != nullptr) {
                // relax()
                chill(u, curArc);
                curArc = curArc->next;
            }

        }

    }

};


#endif //GRAPH_GRAPH_H


