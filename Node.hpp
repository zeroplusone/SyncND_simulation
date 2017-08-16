#ifndef NODE_H
#define NODE_H

#include "Parameter.hpp"
#include <time.h>

class Node {
public:
    Node(int);
    static int nodeIdCounter;
    int id;
    int belongedGroupId;
    double getNextEventTime(int, double);
private:
    double cycleCounter;
    double error_factor;
    void newErrorFactor();
};

#endif