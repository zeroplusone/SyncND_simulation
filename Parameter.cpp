#include "Parameter.hpp"
using namespace std;

double Parameter::SIM_TIME;
double Parameter::DUTY_CYCLE;
double Parameter::SUCCESS_PROB;
double Parameter::UPDATE_FREQ;

const double Parameter::SLOT_DURATION = 5;
const double Parameter::NUMBER_OF_GROUPS = 1;

double Parameter::ACTIVE_DURATION;
double Parameter::SLEEP_DURATION;
int Parameter::NUMBER_OF_CYCLE_PER_UPDATE;
double Parameter::ERROR_BOUND;
double Parameter::GLOBAL_TIME;
priority_queue<Event, vector<Event>, Compare> Parameter::eventList;
vector<Group> Parameter::groupList;
vector<Node> Parameter::syncNodes;

Parameter::Parameter(double simTime, double dutyCycle, double successProb, double updateFreq) {
    SIM_TIME = simTime;
    DUTY_CYCLE = dutyCycle;
    SUCCESS_PROB = successProb;
    UPDATE_FREQ = updateFreq;

    ACTIVE_DURATION = 1 * SLOT_DURATION;
    SLEEP_DURATION = (1 / DUTY_CYCLE - 1) * SLOT_DURATION;
    NUMBER_OF_CYCLE_PER_UPDATE = int(UPDATE_FREQ / (1 / DUTY_CYCLE * SLOT_DURATION));
    ERROR_BOUND = 6.9017 * updateFreq / 1000.0 + 0.0983;
    GLOBAL_TIME = 0;
    groupList.clear();
}

void Parameter::settingDisplay() {
    cout << "======================" << endl;
    cout << "Duty Cycle: " << Parameter::DUTY_CYCLE << endl;
    cout << "Success Probability: " << Parameter::SUCCESS_PROB << endl;
    cout << "update frequency: " << Parameter::UPDATE_FREQ << endl;
    cout << "======================" << endl;
}
