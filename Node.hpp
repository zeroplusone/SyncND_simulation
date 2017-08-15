#ifndef NODE_H
#define NODE_H

class Node {
public:
    Node();
    static int nodeIdCounter;
    int id;
    double getNextEventTime(int, double);
private:
    double timeCounter;
};

#endif