#include "Parameter.hpp"
using namespace std;

double Parameter::SIM_TIME;
double Parameter::DUTY_CYCLE;
double Parameter::SUCCESS_PROB;
double Parameter::UPDATE_FREQ;
const double Parameter::SLOT_DURATION = 5;
double Parameter::ERROR_BOUND;
double Parameter::GLOBAL_TIME;


Parameter::Parameter(double simTime, double dutyCycle, double successProb, double updateFreq) {
    SIM_TIME = simTime;
    DUTY_CYCLE = dutyCycle;
    SUCCESS_PROB = successProb;
    UPDATE_FREQ = updateFreq;
    ERROR_BOUND = 6.9017*updateFreq/1000.0+0.0983;
    GLOBAL_TIME = 0;
}

void Parameter::settingDisplay() {
    cout << "======================" << endl;
    cout << "Duty Cycle: " << Parameter::DUTY_CYCLE << endl;
    cout << "Success Probability: " << Parameter::SUCCESS_PROB << endl;
    cout << "update frequency: " << Parameter::UPDATE_FREQ << endl;
    cout << "======================" << endl;
}
