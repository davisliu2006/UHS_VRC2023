#ifndef GLOBALS_H
#define GLOBALS_H

#include "../include/main.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "custom_math.hpp"
#include "geometry.hpp"

using namespace std;

// DEFINITIONS

// controller
inline pros::Controller master(pros::E_CONTROLLER_MASTER);

// motor constants
const int MTR_MAX = 127;
const int MTR_MAXmV = 12000;
const double GRN_RPM = 200;
const double GRN_RPS = GRN_RPM/60;

// drivetrain
const double WHEEL_R  = 2; // inches
const double WHEEL_C = WHEEL_R*2*M_PI;
const double DRV_R = 9;
const double DRV_C = DRV_R*2*M_PI;
const double DRV_RPS = WHEEL_C*GRN_RPS/DRV_C;
const double DRV_DPS = DRV_RPS*360;
inline pros::Motor flmotor(1);
inline pros::Motor frmotor(10, true);
inline pros::Motor rlmotor(11);
inline pros::Motor rrmotor(20, true);

// intake and shooter
inline pros::Motor intake(5);
inline pros::Motor indexer(6, true);
inline pros::MotorGroup flywheel({pros::Motor(7, pros::E_MOTOR_GEAR_BLUE, true),
    pros::Motor(8, pros::E_MOTOR_GEAR_BLUE, true)});

// expansion
const int ADI_MAX = 4095;
inline pros::ADIDigitalOut expansion(1);

// sensing
const int TILE = 2;
const int FIELD = TILE*6;
const double GRVTY = 9.8;
inline pros::IMU inertial(14);
inline pros::Rotation trackx(15);
inline pros::Rotation tracky(16);

// FUNCTIONS

// math
// inline double rad(double x) {return x*M_PI/180;}
// inline double deg(double x) {return x*180/M_PI;}

// time
#define _time_impl 1
#if _time_impl == 0 // native timer
inline double time() {
    timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t.tv_sec+t.tv_nsec*0.000000001;
}
#elif _time_impl == 1 // pros timer
inline double time() {
    return pros::micros()*0.000001;
}
#endif

// TEMPLATE

enum AutonEnum {
    BLUE_1 = -1, BLUE_2 = -2, BLUE_3 = -3, BLUE_4 = -4, BLUE_5 = -5,
    RED_1 = 1, RED_2 = 2, RED_3 = 3, RED_4 = 4, RED_5 = 5,
    NOTHING = 10, SKILLS = 0
};
inline int autonSelection = SKILLS; // specifies the default auton selected

#endif
