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
private:
    static int groupIdCounter;
    int id;
    vector<Node> nodeList;
    int numberOfNode;
};


#endif