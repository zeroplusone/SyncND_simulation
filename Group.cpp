# include "Group.hpp"

int Group::groupIdCounter = 0;

Group::Group(int numOfNode) {
    // initial group id
    id = groupIdCounter;
    groupIdCounter += 1;

    // create nodes
    numberOfNode = numOfNode;
    // global clock (id=0)
    nodeList.push_back(*(new Node()));
    // devices
    while (numOfNode--) {
        nodeList.push_back(*(new Node()));
    }

    // variable initialization
    while (!eventList.empty()) {
        eventList.pop();
    }
}

void Group::process(Parameter para) {
    cout << "--- Group_" << id << " process ---" << endl;
    for (int i = 0; i <= numberOfNode; ++i) {
        Event e(i, ACTIVE_START, 0);
        eventList.push(e);
    }
    double currentTime = 0;
    while (!eventList.empty()) {
        Event e = eventList.top();
        eventList.pop();
        cout << "- Event(" << e.eventType << "): " << e.time << " " << e.nodeId << endl;
        currentTime = e.time;
        switch (e.eventType) {
        case ACTIVE_START:
            // create end event
            eventList.push(*(new Event(e.nodeId, ACTIVE_END, nodeList[e.nodeId].getNextEventTime(e.eventType, currentTime))));
            // statistic
            break;
        case ACTIVE_END:
            // create next active event
            eventList.push(*(new Event(e.nodeId, ACTIVE_START, nodeList[e.nodeId].getNextEventTime(e.eventType, currentTime))));
            // statistic
            break;
        default:
            cerr << "Error event type!" << endl;
            break;
        }
    }
}