#ifndef EVENT_H
#define EVENT_H

#define ACTIVE_START 0
#define ACTIVE_END 1

class Event {
public:
    Event(int, int, int, double);
    int groupId;
    int nodeId;
    int eventType;
    double time;
};

#endif