#include "Group.hpp"
int Group::groupIdCounter = 0;

Group::Group(int numOfNode)
{
    // initial group id
    id = groupIdCounter;
    groupIdCounter += 1;

    // create nodes
    numberOfNode = numOfNode;
    // global clock (id=0)
    nodeList.push_back(*(new Node(0)));
    // devices
    while (numOfNode--)
    {
        nodeList.push_back(*(new Node(id)));
    }

    // variable initialization
    for (int i = 0; i <= numberOfNode; ++i)
    {
        Event e(id, i, ACTIVE_START, 0);
        Parameter::eventList.push(e);
    }
}

void Group::process(Event e)
{
    // cout << "--- Group_" << id << " process ---" << endl;

    double currentTime = e.time;
    double nextEventTime = nodeList[e.nodeId].getNextEventTime(e.eventType, currentTime);
    if (e.eventType == ACTIVE_START)
        cout << "# Event(START) [" << e.time << "] " << e.groupId << " " << e.nodeId << endl;
    else if (e.eventType == ACTIVE_END)
        cout << "# Event(END) [" << e.time << "] " << e.groupId << " " << e.nodeId << endl;
    switch (e.eventType)
    {
    case ACTIVE_START:
        // create end event
        Parameter::eventList.push(*(new Event(id, e.nodeId, ACTIVE_END, nextEventTime)));
        // statistic
        break;
    case ACTIVE_END:
        // create next active event
        if (nextEventTime >= 0)
            Parameter::eventList.push(*(new Event(id, e.nodeId, ACTIVE_START, nextEventTime)));
        // statistic
        break;
    default:
        cerr << "Error event type!" << endl;
        break;
    }
}