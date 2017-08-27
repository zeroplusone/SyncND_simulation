# include "Event.hpp"
#include <iostream>
using namespace std;

Event::Event(int groupId, int nodeId, int eventType, double time) {
    this->groupId = groupId;
    this->nodeId = nodeId;
    this->eventType = eventType;
    this-> time = time;
}