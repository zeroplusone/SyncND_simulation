#ifndef NODE_H
#define NODE_H

#include "Parameter.hpp"
#include <time.h>
#include <set>
using namespace std;

class Node {
public:
    Node(int, int);
    static int nodeIdCounter;
    int id;
    int idInGroup;
    int belongedGroupId;
    double getNextEventTime(int, double);
    double numberOfSuccessDiscover;
    int cycleCounter;
    set<int> discoverDevices;
    Event* nextEvent;
    void newNextCalibration(double);
private:
    void newErrorFactor();
    double errorFactor;
};

#endif