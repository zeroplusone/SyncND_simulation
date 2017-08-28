#include "Node.hpp"

int Node::nodeIdCounter = 0;

Node::Node(int groupId, int nodeIdInGroup) {
    this->id = nodeIdCounter;
    idInGroup = nodeIdInGroup;
    nodeIdCounter += 1;
    cycleCounter = 0;
    numberOfSuccessDiscover = 0;
    belongedGroupId = groupId;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long timeSeed = tv.tv_usec;
    srand(timeSeed + id);
    errorFactor = 0;
    newErrorFactor();
    discoverDevices.clear();
    activeStatus = 0;
}

void Node::newErrorFactor() {
    int random = rand();
    isFaster = random % 2 == 0 ? 1.0 : -1.0; // decide +-
    double randomBound = isFaster * Parameter::ERROR_BOUND * ((rand() % 100000000) / 100000000.0); // decide value
    // randomBound = randomBound * Parameter::ERROR_BOUND;
    errorFactor = randomBound / Parameter::UPDATE_FREQ;
#ifdef DEBUG
    // cout<<"errorBound"<<Parameter::ERROR_BOUND<<" ,errorFacotr "<<errorFactor<<" ,randomBound "<<randomBound<<" ,updateF "<<Parameter::UPDATE_FREQ<<endl;
#endif
}

void Node::newNextCalibration(double currentTime) {
    newErrorFactor();
    Parameter::eventList.insert(*(new Event(belongedGroupId, idInGroup, CALIBRATION, currentTime + Parameter::UPDATE_FREQ + Parameter::UPDATE_FREQ * errorFactor)));
}

double Node::getNextEventTime(int eventType, double currentTime) {
    double nextEventTime = 0;    // unit: slot

    switch (eventType) {
    case ACTIVE_START:
        cycleCounter++;
        nextEventTime = currentTime + Parameter::ACTIVE_DURATION + Parameter::ACTIVE_DURATION * errorFactor;
        activeStatus = nextEventTime;
        break;
    case ACTIVE_END:
        nextEventTime = currentTime + Parameter::SLEEP_DURATION + Parameter::SLEEP_DURATION * errorFactor;
        activeStatus = (-1) * nextEventTime;
        break;
    case CALIBRATION:
        double newTime;
        if (Parameter::GLOBAL_ACTIVE_STATUS >= 0) {
            newTime = (Parameter::GLOBAL_ACTIVE_STATUS - currentTime) + (Parameter::GLOBAL_ACTIVE_STATUS - currentTime) * errorFactor;
            nextEventTime = currentTime + newTime;
        } else {
            newTime = ((-1) * Parameter::GLOBAL_ACTIVE_STATUS - currentTime) + ((-1) * Parameter::GLOBAL_ACTIVE_STATUS - currentTime) * errorFactor;
            nextEventTime = currentTime + newTime;
        }
        break;
    default:
        cerr << "Error eventType!!" << endl;
        break;
    }

    return nextEventTime;
}