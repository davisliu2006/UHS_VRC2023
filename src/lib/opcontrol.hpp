#ifndef OPCONTROL_H
#define OPCONTROL_H

#include "../globals.hpp"
#include "sensing.hpp"

// maps joystick position to drive speed
inline double joymap(int x){
    return (double(x)/MTR_MAX);
}

inline bool is_opcontrol = false;
inline void opcontrol_start() {
    is_opcontrol = true;
    flmotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    frmotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    rlmotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    rrmotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    double print_time = 0;
    double print_rate = 0.5;
    while (is_opcontrol) {
        // sensing
        sens::update();

        // logging
        print_time += sens::dt;
        if (print_time >= print_rate) {
            cout << sens::t1 << ' ' << sens::dt << '\n';
            cout << sens::rot << ' ' << sens::rot_trg << '\n';
            print_time -= print_rate;
        }

        // drivetrain
        double x = joymap(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));
        double y = joymap(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
        double rot = joymap(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
        double rotdev = 0;
        /*if (rot == 0) {
            if (sens::rot_trg == -1) {
                sens::rot_trg = sens::rot;
            } else {
                rotdev = angl_180(sens::rot-sens::rot_trg)/360;
            }
        } else {
            sens::rot_trg = -1;
        }*/
        flmotor.move_velocity((y+x+rot-rotdev)*GRN_RPM);
        frmotor.move_velocity((y-x-rot+rotdev)*GRN_RPM);
        rlmotor.move_velocity((y-x+rot-rotdev)*GRN_RPM);
        rrmotor.move_velocity((y+x-rot+rotdev)*GRN_RPM);

        // intake
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            intake.move(MTR_MAX);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intake.move(-MTR_MAX);
        } else {
            intake.move(0);
        }

        // shooter
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            flywheel.move(MTR_MAX);
        } else {
            flywheel.move(0);
        }
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            indexer.move(MTR_MAX);
        } else {
            indexer.move(-MTR_MAX);
        }

        // expansion
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
            expansion.set_value(ADI_MAX);
            pros::delay(1000);
            expansion.set_value(0);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
            expansion.set_value(0);
        }
    }
}

#endif
