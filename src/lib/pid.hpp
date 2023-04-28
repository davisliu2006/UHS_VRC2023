#pragma once

#include "../include/main.h"
#include <math.h>

namespace pid {
    double PID(double input, double target, double Kp, double Ki, double Kd, int &prevError, int &integral, int direction = 1) {    
        double error = (target - input) * direction;
        double derivative = error - prevError;  // only an approximation
        integral = 0.5 * integral + error;  // only an approximation
        prevError = error;

        return Kp * error + Kd * derivative + Ki * integral;
    }
}