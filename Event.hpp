#ifndef EVENT_H
#define EVENT_H

#define ACTIVE_START 1
#define ACTIVE_END 2
#define CALIBRATION 0

class Event {
public:
    // Event();
    Event(int, int, int, double);
    int groupId;
    int nodeId;
    int eventType;
    double time;
};

#endif