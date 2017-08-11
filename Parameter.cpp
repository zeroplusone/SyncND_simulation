#ifndef _PARAMETER_H
#define _PARAMETER_H

#include "Parameter.hpp"
using namespace std;

double Parameter::DUTY_CYCLE;
double Parameter::SUCCESS_PROB;
int Parameter::UPDATE_FREQ;

Parameter::Parameter(double dutyCycle, double successProb, int updateFreq) {
    DUTY_CYCLE = dutyCycle;
    SUCCESS_PROB = successProb;
    UPDATE_FREQ = updateFreq;
}

void Parameter::settingDisplay() {
    cout << "======================" << endl;
    cout << "Duty Cycle: " << Parameter::DUTY_CYCLE << endl;
    cout << "Success Probability: " << Parameter::SUCCESS_PROB << endl;
    cout << "update frequency: " << Parameter::UPDATE_FREQ << endl;
    cout << "======================" << endl;
}

#endif