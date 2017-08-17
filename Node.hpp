#ifndef NODE_H
#define NODE_H

#include "Parameter.hpp"
#include <time.h>

class Node {
public:
    Node(int, int);
    static int nodeIdCounter;
    int id;
    int idInGroup;
    int belongedGroupId;
    double getNextEventTime(int, double);
    double numberOfSuccessDiscover;
    bool isActive;
    int cycleCounter;
private:
    double errorFactor;
    void newErrorFactor();
};

#endif