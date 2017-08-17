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
    for (int i = 0; i < nodeList.size(); ++i) {
        Event e(id, nodeList[i].idInGroup, ACTIVE_START, 0);
        Parameter::eventList.push(e);
    }

    activeSet.clear();
}

void Group::process(Event e) {
    // cout << "--- Group_" << id << " process ---" << endl;

    double currentTime = e.time;
    double nextEventTime = nodeList[e.nodeId].getNextEventTime(e.eventType, currentTime);
    switch (e.eventType) {
    case ACTIVE_START:
        // create end event
        Parameter::eventList.push(*(new Event(id, e.nodeId, ACTIVE_END, nextEventTime)));
        // statistic
        startStat(e.nodeId);
        break;
    case ACTIVE_END:
        // create next active event
        if (nextEventTime >= 0) {
            Parameter::eventList.push(*(new Event(id, e.nodeId, ACTIVE_START, nextEventTime)));
        }
        else {
            Parameter::syncNodes.push_back(e.nodeId);
        }
        // statistic
        endStat(e.nodeId);
        break;
    default:
        cerr << "Error event type!" << endl;
        break;
    }
}

void Group::startStat(int nodeId) {
    // add success to existing activate node
    set<int>::iterator it;
    for (it = activeSet.begin(); it != activeSet.end(); ++it) {
        nodeList[*(it)].numberOfSuccessDiscover++;
    }
    // add # of existing activate node to its' success counter
    nodeList[nodeId].numberOfSuccessDiscover += activeSet.size();
    // add itself to activate node list
    activeSet.insert(nodeId);
}

void Group::endStat(int nodeId) {
    // remove from activate node list
    activeSet.erase(activeSet.find(nodeId));
}

void Group::totalStat() {
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