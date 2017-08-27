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
            // sync(e.time);
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
            // if (nextEventTime >= 0) {
            // nodeList[e.nodeId].nextEvent = new Event(id, e.nodeId, ACTIVE_START, nextEventTime);
            // Parameter::eventList.insert(*(nodeList[e.nodeId].nextEvent));
            newEvent = *(new Event(id, e.nodeId, ACTIVE_START, nextEventTime));
            Parameter::eventList.insert(newEvent);
            nodeList[e.nodeId].nextEvent = Parameter::eventList.find(newEvent);
            // }
            // else {
            // Parameter::eventList.push(*(new Event(id, e.nodeId, SYNC_START, (-1)*nextEventTime)));
            // }
            // statistic
            endStat(e.nodeId);
            break;
        case CALIBRATION:
            if (Parameter::GLOBAL_ACTIVE_STATUS * nodeList[e.nodeId].activeStatus >= 0) {
                // nodeList[e.nodeId].nextEvent->time = nextEventTime;
                newEvent = *(nodeList[e.nodeId].nextEvent);
                Parameter::eventList.erase(nodeList[e.nodeId].nextEvent);
                newEvent.time = nextEventTime;
                // for (set<Event>::iterator it = Parameter::eventList.begin(); it != Parameter::eventList.end(); ++it)
                //     cout << it->groupId << " " << it->nodeId << " " << it->eventType << " " << it->time << endl;
                Parameter::eventList.insert(newEvent);
                nodeList[e.nodeId].nextEvent = Parameter::eventList.find(newEvent);

                // for (set<Event>::iterator it = Parameter::eventList.begin(); it != Parameter::eventList.end(); ++it)
                //     cout <<"!"<< it->groupId << " " << it->nodeId << " " << it->eventType << " " << it->time << endl;
            } else {
                if (nodeList[e.nodeId].activeStatus >= 0) {

                    newEvent = *(new Event(id, e.nodeId, ACTIVE_END, currentTime));
                    Parameter::eventList.erase(nodeList[e.nodeId].nextEvent);
                    Parameter::eventList.insert(newEvent);
                    // newEvent.eventType = ACTIVE_START;
                    // newEvent.time = (-1) * nextEventTime;
                    // // for (set<Event>::iterator it = Parameter::eventList.begin(); it != Parameter::eventList.end(); ++it)
                    // //     cout << it->groupId << " " << it->nodeId << " " << it->eventType << " " << it->time << endl;
                    // Parameter::eventList.insert(newEvent);
                    nodeList[e.nodeId].nextEvent = Parameter::eventList.find(newEvent);

                } else {

                    newEvent = *(new Event(id, e.nodeId, ACTIVE_START, currentTime));
                    Parameter::eventList.erase(nodeList[e.nodeId].nextEvent);
                    Parameter::eventList.insert(newEvent);
                    // newEvent.eventType = ACTIVE_END;
                    // newEvent.time = nextEventTime;
                    // // for (set<Event>::iterator it = Parameter::eventList.begin(); it != Parameter::eventList.end(); ++it)
                    // //     cout << it->groupId << " " << it->nodeId << " " << it->eventType << " " << it->time << endl;
                    // Parameter::eventList.insert(newEvent);
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
        // cout << "@" << nodeList[i].numberOfSuccessDiscover << " " << nodeList[i].cycleCounter << endl;
        nodeProb = nodeList[i].numberOfSuccessDiscover / (nodeList.size() - 1) / nodeList[i].cycleCounter;
        cout << "  Node " << i << ": " << nodeProb << endl;
        averageProb += nodeProb;
    }
    cout << "Average: " << averageProb / nodeList.size() << endl;
}