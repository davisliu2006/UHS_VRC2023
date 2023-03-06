#pragma once

#include "../globals.hpp"
#include "sensing.hpp"

// maps joystick position to drive speed
inline double joymap(int x){
    double temp = double(x)/MTR_MAX;
    return temp*sqrt(abs(temp));
}

inline bool is_opcontrol = false;
inline void opcontrol_start() {
    is_opcontrol = true;

    // logging
    double print_time = 0;
    double print_delay = 1; // required to prevent output lag

    // drivetrain
    int drv_rev = 1; // reverse drivetrain

    while (is_opcontrol) {
        // sensing
        sens::update();

        // logging
        print_time += sens::dt;
        if (print_time >= print_delay) {
            cout << sens::t << ' ' << sens::dt << '\n';
            cout << sens::rot << ' ' << sens::rot_trg << '\n';
            print_time -= print_delay;
        }

        // drivetrain
        double x = joymap(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X))*drv_rev;
        double y = joymap(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y))*drv_rev;
        double rot = joymap(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
        #if DRV_MODE == TANK_DRV
        flmotor.move_velocity((y+rot)*WHEEL_RPM);
        frmotor.move_velocity((y-rot)*WHEEL_RPM);
        rlmotor.move_velocity((y+rot)*WHEEL_RPM);
        rrmotor.move_velocity((y-rot)*WHEEL_RPM);
        #elif DRV_MODE == X_DRV
        flmotor.move_velocity((y+x+rot)*WHEEL_RPM);
        frmotor.move_velocity((y-x-rot)*WHEEL_RPM);
        rlmotor.move_velocity((y-x+rot)*WHEEL_RPM);
        rrmotor.move_velocity((y+x-rot)*WHEEL_RPM);
        #endif

        // intake
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intake.move(MTR_MAX);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            intake.move(-MTR_MAX);
        } else {
            intake.move(0);
        }

        // shooter
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            flywheel.move(MTR_MAX);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            flywheel.move(-MTR_MAX);
        } else {
            flywheel.move(0);
        }
        #if INDEXER_TYPE == TYPE_MTR
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            indexer.move_absolute(55, INDX_RPM);
        } else {
            indexer.move_absolute(0, INDX_RPM);
        }
        #elif INDEXER_TYPE == TYPE_PNEU
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            indexer.set_value(ADI_MAX);
        } else {
            indexer.set_value(0);
        }
        #endif

        // drivetrain reverse
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) { // shooter front
            drv_rev = 1;
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) { // intake front
            drv_rev = -1;
        }

        // expansion
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)
        && master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)
        && master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)
        && master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)
        && master.get_digital(pros::E_CONTROLLER_DIGITAL_A)
        && master.get_digital(pros::E_CONTROLLER_DIGITAL_B)
        && master.get_digital(pros::E_CONTROLLER_DIGITAL_X)
        && master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
            expansion.set_value(ADI_MAX);
            pros::delay(1000);
            expansion.set_value(0);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
            expansion.set_value(0);
        }
    }
}