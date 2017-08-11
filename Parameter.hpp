#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <cstdlib>
using namespace std;

class Parameter {
public:
    Parameter(double, double, int);
    static double DUTY_CYCLE; // duty cycle => energy consumption
    static double SUCCESS_PROB; // assuring probability of success
    static int UPDATE_FREQ; // update frequency in hour

    void settingDisplay();
};

#endif