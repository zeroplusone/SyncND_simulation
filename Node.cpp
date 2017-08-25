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
    discoverDevices.clear();
}

void Node::newErrorFactor() {
    double randomBound = rand() % 2 == 0 ? 1.0 : (-1.0); // decide +-
    randomBound = randomBound * (rand() % int((Parameter::ERROR_BOUND) * 100)) / 100; // decide value
    errorFactor = 1 + randomBound / Parameter::UPDATE_FREQ;
}

void Node::newNextCalibration(double currentTime){
    newErrorFactor();
    Parameter::eventList.push(*(new Event(belongedGroupId, idInGroup, CALIBRATION, currentTime + Parameter::UPDATE_FREQ*errorFactor)));

}

double Node::getNextEventTime(int eventType, double currentTime) {
    double nextEventTime = 0;    // unit: slot

    switch (eventType) {
    case ACTIVE_START:
        cycleCounter++;
        nextEventTime = currentTime + Parameter::ACTIVE_DURATION * errorFactor;
        break;
    case ACTIVE_END:
        nextEventTime = currentTime + Parameter::SLEEP_DURATION * errorFactor;
        cout<<"~"<<belongedGroupId<<" "<<idInGroup<<" "<< nextEventTime<<endl;
        break;
    case CALIBRATION:
        cout<<"!!"<<Parameter::GLOBAL_ACTIVE_STATUS<<endl;
        double newTime;
        if (Parameter::GLOBAL_ACTIVE_STATUS >= 0) {
            newTime=(Parameter::GLOBAL_ACTIVE_STATUS - currentTime) * errorFactor;
            cout<<"#"<<newTime<<endl;
            nextEventTime = currentTime + newTime;
        } else {
            newTime = ((-1) * Parameter::GLOBAL_ACTIVE_STATUS - currentTime) * errorFactor;
            cout<<"##"<<newTime<<endl;
            nextEventTime = currentTime + newTime;
        }
        break;
    default:
        cerr << "Error eventType!!" << endl;
        break;
    }

    return nextEventTime;
}