#include "Node.hpp"

int Node::nodeIdCounter = 0;

Node::Node(int groupId, int nodeIdInGroup) {
    this->id = nodeIdCounter;
    idInGroup = nodeIdInGroup;
    nodeIdCounter += 1;
    cycleCounter = 0;
    numberOfSuccessDiscover = 0;
    belongedGroupId = groupId;
    srand(time(NULL) + id);
    errorFactor = 0;
    newErrorFactor();
    isActive = true;
    discoverDevices.clear();
}

void Node::newErrorFactor() {
    double randomBound = rand() % 2 == 0 ? 1.0 : (-1.0); // decide +-
    randomBound = randomBound * (rand() % int((Parameter::ERROR_BOUND) * 100)) / 100; // decide value
    errorFactor = 1 + randomBound / Parameter::UPDATE_FREQ;
}

double Node::getNextEventTime(int eventType, double currentTime) {
    double nextEventTime = 0;    // unit: slot

    switch (eventType) {
    case ACTIVE_START:
        cycleCounter++;
        nextEventTime = currentTime + Parameter::ACTIVE_DURATION * errorFactor;
        break;
    case ACTIVE_END:
        if (cycleCounter % Parameter::NUMBER_OF_CYCLE_PER_UPDATE == 0) {
            nextEventTime = -1;
        } else {
            nextEventTime = currentTime + Parameter::SLEEP_DURATION * errorFactor;
        }
        break;
    default:
        break;
    }

    return nextEventTime;
}