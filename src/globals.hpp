#pragma once

#include "../include/main.h"

#include <algorithm>
#include <array>
#include <cmath>
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
constexpr int MTR_MAX = 127;
constexpr int MTR_MAXmV = 12000;
constexpr double GRN_RPM = 200;
constexpr double GRN_RPS = GRN_RPM/60;

// drivetrain
constexpr double WHEEL_R  = 2; // inches
constexpr double WHEEL_C = WHEEL_R*M_PI*2;
constexpr double DRV_R = 9;
constexpr double DRV_C = DRV_R*M_PI*2;
constexpr double DRV_RPS = WHEEL_C*GRN_RPS/DRV_C;
constexpr double DRV_DPS = DRV_RPS*360;
inline pros::Motor flmotor(7);
inline pros::Motor frmotor(9, true);
inline pros::Motor rlmotor(8);
inline pros::Motor rrmotor(10, true);

// intake and shooter
inline pros::Motor intake(6);
inline pros::Motor indexer(5);
inline pros::MotorGroup flywheel({pros::Motor(3, pros::E_MOTOR_GEAR_BLUE, true),
    pros::Motor(4, pros::E_MOTOR_GEAR_BLUE, true)});

// expansion
const int ADI_MAX = 4095;
// inline pros::ADIDigitalOut expansion(4);

// sensing
const int TILE = 24; // inches
const int FIELD = TILE*6;
const double GRVTY = 9.8;
inline pros::IMU inertial(1);
inline pros::Rotation trackx(15);
inline pros::Rotation tracky(16);

// FUNCTIONS

// time
#define _time_impl 1
#if _time_impl == 0 // uses native timer
inline double time() {
    timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t.tv_sec+t.tv_nsec*0.000000001;
}
#elif _time_impl == 1 // uses pros timer
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