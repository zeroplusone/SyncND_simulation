#ifndef NODE_H
#define NODE_H

#include "Parameter.hpp"
#include <sys/time.h>
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
    double cycleCounter;
    set<int> discoverDevices;
    set<Event>::iterator nextEvent;
    double activeStatus;
    void newNextCalibration(double);
private:
    void newErrorFactor();
    double isFaster;
    double errorFactor;
};

#endif