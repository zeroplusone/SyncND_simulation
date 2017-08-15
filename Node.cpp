#include "Node.hpp"
#include "Parameter.hpp"

int Node::nodeIdCounter = 0;

Node::Node() {
    this->id = nodeIdCounter;
    nodeIdCounter += 1;
    timeCounter=0;
}

double Node::getNextEventTime(int eventType, double currentTime) {
        
    return Parameter::SLOT_DURATION;
}