# include "Group.hpp"

int Group::groupIdCounter = 0;

Group::Group(int numOfNode) {
    // initial group id
    id = groupIdCounter;
    groupIdCounter += 1;

    // create nodes
    numberOfNode = numOfNode;
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
    
    for (int i = 0; i < numberOfNode; ++i) {
        Event e(i, ACTIVE_START, 0);
        eventList.push(e);
    }

    while (!eventList.empty()) {
        Event e = eventList.top();
        eventList.pop();
        cout << "- Event(" << e.eventType << "): " << e.time << " " << e.nodeId << endl;
        switch(e.eventType){
            case ACTIVE_START:
                break;
            case ACTIVE_END:
                break;
            default:
                cerr<<"Error event type!"<<endl;
                break;
        }
    }
    


}