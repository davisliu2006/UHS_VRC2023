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

#include "headers/custom_math.hpp"
#include "headers/geometry.hpp"

using namespace std;

// SETTINGS

#define TANK_DRV 1
#define X_DRV 2
#define DRV_MODE TANK_DRV

// DEFINITIONS

// controller
inline pros::Controller master(pros::E_CONTROLLER_MASTER);

// motor constants
const int MTR_MAX = 127;
const int MTR_MAXmV = 12000;
const double GRN_RPM = 200;
const double GRN_RPS = GRN_RPM/60;
const double BLU_RPM = 600;
const double BLU_RPS = BLU_RPM/60;

// drivetrain
const double WHEEL_R  = 2; // inches
const double WHEEL_C = WHEEL_R*M_PI*2;
const double DRV_R = 9;
const double DRV_C = DRV_R*M_PI*2;
const double DRV_RPS = WHEEL_C*GRN_RPS/DRV_C;
const double DRV_DPS = DRV_RPS*360;
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
inline pros::ADIDigitalOut expansion(11);

// sensing
const int TILE = 24; // inches
const int FIELD = TILE*6;
const double GRVTY = 9.8;
inline pros::IMU inertial(1);
inline pros::Rotation trackx(15);
inline pros::Rotation tracky(16);

// FUNCTIONS

// time
#define TIME_IMPL 1
#if TIME_IMPL == 0 // uses native timer
inline double time() {
    timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t.tv_sec+t.tv_nsec*0.000000001;
}
#elif TIME_IMPL == 1 // uses pros timer
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