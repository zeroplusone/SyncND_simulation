#ifndef GROUP_H
#define GROUP_H

#include "Parameter.hpp"
#include "Node.hpp"
#include "Event.hpp"
#include <vector>
#include <iostream>
#include <queue>
#include <set>
using namespace std;

class Parameter;
class Node;
class Event;
class Group {
public:
    Group(int);
    void process(Event e);
    vector<Node> nodeList;
    void totalStat();
private:
    static int groupIdCounter;
    int id;
    int numberOfNode;
    // for statistic
    void startStat(int);
    void endStat(int);
    set<int> activeSet;
};


#endif