#include "Parameter.hpp"
using namespace std;

double Parameter::SIM_TIME;
double Parameter::DUTY_CYCLE;
double Parameter::SUCCESS_PROB;
double Parameter::UPDATE_FREQ;
double Parameter::SLOT_DURATION;

const double Parameter::NUMBER_OF_GROUPS = 1;

double Parameter::ACTIVE_DURATION;
double Parameter::SLEEP_DURATION;
int Parameter::NUMBER_OF_CYCLE_PER_UPDATE;
double Parameter::ERROR_BOUND;
double Parameter::GLOBAL_TIME;
double Parameter::GLOBAL_ACTIVE_STATUS;
double Parameter::GLOBAL_CYCLE_COUNTER;
double Parameter::GLOBAL_CALIBRATION_COUNTER;
set<Event, Compare> Parameter::eventList;
vector<Group> Parameter::groupList;
vector<int> Parameter::syncNodes;

Parameter::Parameter(double simTime, double dutyCycle, double updateFreq, double slotDuration) {
    SIM_TIME = simTime;
    DUTY_CYCLE = dutyCycle;
    UPDATE_FREQ = updateFreq;
    SLOT_DURATION = slotDuration;

    SUCCESS_PROB = 0;

    ACTIVE_DURATION = 1 * SLOT_DURATION;
    SLEEP_DURATION = (int(1 / DUTY_CYCLE) - 1) * SLOT_DURATION;
    // round up
    NUMBER_OF_CYCLE_PER_UPDATE = int(ceil(UPDATE_FREQ / (1 / DUTY_CYCLE * SLOT_DURATION)));
    // ERROR_BOUND = 6.9017 * updateFreq / 1000.0 + 0.0983;
    ERROR_BOUND = 3e-16 * UPDATE_FREQ * UPDATE_FREQ + 2e-8 * UPDATE_FREQ;
    GLOBAL_TIME = 0;
    GLOBAL_ACTIVE_STATUS = ACTIVE_DURATION;
    GLOBAL_CYCLE_COUNTER = 0;
    GLOBAL_CALIBRATION_COUNTER = 0;
    groupList.clear();
}

void Parameter::settingDisplay() {
    cout << "======================" << endl;
    cout << "Simulation Time: " << SIM_TIME << endl;
    cout << "Duty Cycle: " << DUTY_CYCLE << endl;
    cout << "update frequency: " << UPDATE_FREQ << endl;
    cout << "slot duration: " << SLOT_DURATION << endl;
    cout << "======================" << endl;
}

bool Parameter::checkSetting() {
    if (DUTY_CYCLE >= 0 && DUTY_CYCLE <= 1)
        return true;
    return false;
}
