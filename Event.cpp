# include "Event.hpp"
#include <iostream>
using namespace std;
// Event::Event() {
//     this->groupId = -1;
//     this->nodeId = -1;
//     this->eventType = -1;
//     this-> time = -1;
// }

Event::Event(int groupId, int nodeId, int eventType, double time) {
    this->groupId = groupId;
    this->nodeId = nodeId;
    this->eventType = eventType;
    this-> time = time;
}