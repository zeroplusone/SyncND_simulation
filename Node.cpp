#include "Node.hpp"

int Node::nodeIdCounter = 0;

Node::Node(int groupId) {
    this->id = nodeIdCounter;
    nodeIdCounter += 1;
    cycleCounter = 0;
    belongedGroupId = groupId;
    srand(time(NULL));
    error_factor = 0;
    newErrorFactor();
}

void Node::newErrorFactor() {
    double randomBound = rand() % 2 == 0 ? 1.0 : (-1.0); // decide +-
    randomBound = randomBound * (rand() % int((Parameter::ERROR_BOUND) * 100)) / 100; // decide value
    error_factor = 1 + randomBound / Parameter::UPDATE_FREQ;
}

double Node::getNextEventTime(int eventType, double currentTime) {
    double nextEventTime = 0;    // unit: slot

    switch (eventType) {
    case ACTIVE_START:
        nextEventTime = currentTime + Parameter::ACTIVE_DURATION * error_factor;
        break;
    case ACTIVE_END:
        cycleCounter++;
        if (cycleCounter >= Parameter::NUMBER_OF_CYCLE_PER_UPDATE) {
            nextEventTime = -1;
            Parameter::syncNodes.push_back((*this));
            cycleCounter = 0;
        } else {
            nextEventTime = currentTime + Parameter::SLEEP_DURATION * error_factor;
        }
        break;
    default:
        break;
    }

    return nextEventTime;
}