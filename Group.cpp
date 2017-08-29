#include "Group.hpp"
int Group::groupIdCounter = 0;

Group::Group(int numOfNode) {
    // initial group id
    id = groupIdCounter;
    groupIdCounter += 1;

    // create nodes
    numberOfNode = numOfNode;
    // devices
    for (int i = 0; i < numOfNode; ++i) {
        nodeList.push_back(*(new Node(id, i)));
    }

    // variable initialization
    if (id == 0) {
        for (int i = 0; i < nodeList.size(); ++i) {
            Event e(id, nodeList[i].idInGroup, ACTIVE_START, 0);
            Parameter::eventList.insert(e);
        }
    } else {
        for (int i = 0; i < nodeList.size(); ++i) {
            Event e(id, nodeList[i].idInGroup, ACTIVE_START, 0);
            Parameter::eventList.insert(e);
            nodeList[i].newNextCalibration(0);
        }
    }

    activeSet.clear();
}

void Group::process(Event e) {
    // cout << "--- Group_" << id << " process ---" << endl;

    if (e.groupId == 0) {
        switch (e.eventType) {
        case ACTIVE_START:
            Parameter::GLOBAL_CYCLE_COUNTER ++;
            Parameter::GLOBAL_ACTIVE_STATUS = e.time + Parameter::ACTIVE_DURATION;
            Parameter::eventList.insert(*(new Event(0, 0, ACTIVE_END, e.time + Parameter::ACTIVE_DURATION)));
            break;
        case ACTIVE_END:
            Parameter::GLOBAL_ACTIVE_STATUS = (-1) * (e.time + Parameter::SLEEP_DURATION);
            Parameter::eventList.insert(*(new Event(0, 0, ACTIVE_START, e.time + Parameter::SLEEP_DURATION)));
            break;
        default:
            cerr << "Error eventType!!" << endl;
            break;
        }
    } else {
        double currentTime = e.time;
        double nextEventTime = nodeList[e.nodeId].getNextEventTime(e.eventType, currentTime);
        Event newEvent(0, 0, 0, 0);
        switch (e.eventType) {
        case ACTIVE_START:
            // create end event
            newEvent = *(new Event(id, e.nodeId, ACTIVE_END, nextEventTime));
            Parameter::eventList.insert(newEvent);
            nodeList[e.nodeId].nextEvent = Parameter::eventList.find(newEvent);
            // statistic
            startStat(e.nodeId);
            break;
        case ACTIVE_END:
            // create next active event
            newEvent = *(new Event(id, e.nodeId, ACTIVE_START, nextEventTime));
            Parameter::eventList.insert(newEvent);
            nodeList[e.nodeId].nextEvent = Parameter::eventList.find(newEvent);
            // statistic
            endStat(e.nodeId);
            break;
        case CALIBRATION:
            Parameter::GLOBAL_CALIBRATION_COUNTER ++;
            if (Parameter::GLOBAL_ACTIVE_STATUS * nodeList[e.nodeId].activeStatus >= 0) {
                // at correct active status

                // calibrate next event time (remove old one and add new one)
                newEvent = *(nodeList[e.nodeId].nextEvent);
                Parameter::eventList.erase(nodeList[e.nodeId].nextEvent);
                newEvent.time = nextEventTime;
                Parameter::eventList.insert(newEvent);
                nodeList[e.nodeId].nextEvent = Parameter::eventList.find(newEvent);

            } else {
                // at wrong active status
                if (nodeList[e.nodeId].activeStatus >= 0) {
                    // immediate turn on and remove old one
                    newEvent = *(new Event(id, e.nodeId, ACTIVE_END, currentTime));
                    Parameter::eventList.erase(nodeList[e.nodeId].nextEvent);
                    Parameter::eventList.insert(newEvent);
                    nodeList[e.nodeId].nextEvent = Parameter::eventList.find(newEvent);

                } else {
                    // immediate turn off and remove old one
                    newEvent = *(new Event(id, e.nodeId, ACTIVE_START, currentTime));
                    Parameter::eventList.erase(nodeList[e.nodeId].nextEvent);
                    Parameter::eventList.insert(newEvent);
                    nodeList[e.nodeId].nextEvent = Parameter::eventList.find(newEvent);
                }
            }
            nodeList[e.nodeId].newNextCalibration(currentTime);
            break;
        default:
            cerr << "Error event type!" << endl;
            break;
        }
    }

}

void Group::startStat(int nodeId) {
    // add success to existing activate node
    set<int>::iterator it;
    for (it = activeSet.begin(); it != activeSet.end(); ++it) {
        //nodeList[*(it)].numberOfSuccessDiscover++;
        nodeList[*(it)].discoverDevices.insert(nodeId);
        nodeList[nodeId].discoverDevices.insert(*(it));

    }
    // add # of existing activate node to its' success counter
    // nodeList[nodeId].numberOfSuccessDiscover += activeSet.size();
    // add itself to activate node list
    activeSet.insert(nodeId);
}

void Group::endStat(int nodeId) {
    // remove from activate node list
    activeSet.erase(activeSet.find(nodeId));
    nodeList[nodeId].numberOfSuccessDiscover += nodeList[nodeId].discoverDevices.size();
    nodeList[nodeId].discoverDevices.clear();
}

void Group::totalStat() {
    // end all active event
    set<int>::iterator it;
    for (it = activeSet.begin(); it != activeSet.end(); ++it) {
        nodeList[*(it)].numberOfSuccessDiscover += nodeList[*(it)].discoverDevices.size();
        nodeList[*(it)].discoverDevices.clear();
    }
    double nodeProb;
    double averageProb = 0;
    for (int i = 0; i < nodeList.size(); ++i) {
        // display counting number
        cout << "@" << nodeList[i].numberOfSuccessDiscover << " " << nodeList[i].cycleCounter << endl;
        nodeProb = nodeList[i].numberOfSuccessDiscover / (nodeList.size() - 1) / nodeList[i].cycleCounter;
        cout << "  Node " << i << ": " << nodeProb << endl;
        averageProb += nodeProb;
    }
    cout << "Average: " << averageProb / nodeList.size() << endl;
}