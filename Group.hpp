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

struct Compare{
    bool operator()(const Event& a, const Event& b)const {
        return a.time>b.time;
    }
};
class Parameter;
class Node;
class Event;
class Group {
public:
    Group(int);
    void process(Parameter);
private:
    static int groupIdCounter;
    int id;
    vector<Node> nodeList;
    priority_queue<Event, vector<Event>, Compare> eventList;
    int numberOfNode;
};


#endif