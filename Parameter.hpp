#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <cmath>
#include "Event.hpp"
#include "Group.hpp"
#include "Node.hpp"
using namespace std;

struct Compare {
    bool operator()(const Event& a, const Event& b)const {
        return a.time == b.time ? a.groupId > b.groupId : a.time > b.time;
    }
};

class Event;
class Group;
class Node;
class Parameter {
public:
    Parameter(double, double, double, double);
    static double SIM_TIME; // simulation time
    static double DUTY_CYCLE; // duty cycle => energy consumption
    static double SUCCESS_PROB; // assuring probability of success
    static double UPDATE_FREQ; // update frequency in ms

    static const double NUMBER_OF_GROUPS; // number of groups

    static double SLOT_DURATION; // in ms
    static double ACTIVE_DURATION; // in ms
    static double SLEEP_DURATION; // in ms
    static int NUMBER_OF_CYCLE_PER_UPDATE; // one cycle include active and sleep period
    static double ERROR_BOUND;  // +- value in ms
    static double GLOBAL_TIME;
    static double GLOBAL_ACTIVE_STATUS; // >= 0 the time of active end, -1 not on
    static priority_queue<Event, vector<Event>, Compare> eventList;
    static vector<Group> groupList;
    static vector<int> syncNodes;
    void settingDisplay();
    bool checkSetting();
};

#endif