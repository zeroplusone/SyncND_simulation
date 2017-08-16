#include "Group.hpp"
int Group::groupIdCounter = 0;

Group::Group(int numOfNode)
{
    // initial group id
    id = groupIdCounter;
    groupIdCounter += 1;

    // create nodes
    numberOfNode = numOfNode;
    // devices
    for (int i = 0; i < numOfNode; ++i)
    {
        nodeList.push_back(*(new Node(id, i)));
    }

    // variable initialization
    for (int i = 0; i < nodeList.size(); ++i)
    {
        Event e(id, nodeList[i].idInGroup, ACTIVE_START, 0);
        Parameter::eventList.push(e);
    }
}

void Group::process(Event e)
{
    // cout << "--- Group_" << id << " process ---" << endl;

    double currentTime = e.time;
    double nextEventTime = nodeList[e.nodeId].getNextEventTime(e.eventType, currentTime);
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
        else
            Parameter::syncNodes.push_back(e.nodeId);
        // statistic
        break;
    default:
        cerr << "Error event type!" << endl;
        break;
    }
}