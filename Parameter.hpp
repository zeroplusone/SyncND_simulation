#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <cstdlib>
using namespace std;

class Parameter {
public:
    Parameter(double, double, double, double);
    static double SIM_TIME; // simulation time
    static double DUTY_CYCLE; // duty cycle => energy consumption
    static double SUCCESS_PROB; // assuring probability of success
    static double UPDATE_FREQ; // update frequency in ms
    static const double SLOT_DURATION; // in ms
    static double ERROR_BOUND;  // +- value in ms
    static double GLOBAL_TIME;
    void settingDisplay();
};

#endif