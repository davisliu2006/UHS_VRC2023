#pragma once

#include "../globals.hpp"
#include "sensing.hpp"

inline vector2 blue_hi(-2.5, -2.5);
inline vector2 red_lo(-1, -1);
inline vector2 red_hi(2.5, 2.5);
inline vector2 blue_lo(1, 1);
inline vector<vector2> rollers = {
    vector2(1.75, -3), vector2(3, -1.75),
    vector2(-3, 1.75), vector2(-1.75, 3)
};
inline vector<vector2> disks = {
    // diangonal
    vector2(-0.5, 0.5), vector2(-1, 1), vector2(-1.5, 1.5),
    vector2(-2, 2), vector2(-2.5, 2.5),
    vector2(0.5, -0.5), vector2(1, -1), vector2(1.5, -1.5),
    vector2(2, -2), vector2(2.5, -2.5),
    // next to diagonal
    vector2(-0.5, 1.5), vector2(0, 1), vector2(-.5, 0.5), /*skip*/ vector2(1.5, -0.5),
    vector2(-1.5, 0.5), /*skip*/ vector2(-0.5, -0.5), vector2(0, -1), vector2(0.5, -1.5),
    // edge
};

namespace auton {
    const double TURN_MINDIFF = 5;
    const double TURN_MAXDIFF = 100;

    [[deprecated]] inline void advance(int left, int right) {
        flmotor.move_velocity(left);
        frmotor.move_velocity(right);
        rlmotor.move_velocity(left);
        rrmotor.move_velocity(right);
    }
    [[deprecated]] inline void strafe(int left, int right) {
        flmotor.move_velocity(left);
        frmotor.move_velocity(left);
        rlmotor.move_velocity(right);
        rrmotor.move_velocity(right);
    }

    inline void slide(int x, int y) {
        flmotor.move_velocity(y+x);
        frmotor.move_velocity(y-x);
        rlmotor.move_velocity(y-x);
        rrmotor.move_velocity(y+x);
    }
    inline void turn(int rotvel) {
        flmotor.move_velocity(rotvel);
        frmotor.move_velocity(-rotvel);
        rlmotor.move_velocity(rotvel);
        rrmotor.move_velocity(-rotvel);
    }

    inline void stop() {
        flmotor.move_velocity(0);
        frmotor.move_velocity(0);
        rlmotor.move_velocity(0);
        rrmotor.move_velocity(0);
    }

    [[deprecated]] inline void slide_time(int x, int y, double dt) {
        slide(x, y);
        while (dt > 0) {
            sens::update();
            dt -= sens::dt;
        }
        slide(0, 0);
    }
    inline void slide_dist(double dist, double ang, double vel) { // inches
        ang -= 45;
        ang = rad(ang);
        const double cosine = cos(ang), sine = sin(ang);
        double angx = dist*cosine/WHEEL_C;
        double angy = dist*sine/WHEEL_C;
        double velx = vel*cosine;
        double vely = vel*sine;

        flmotor.move_relative(angx, velx);
        frmotor.move_relative(-angy, vely);
        rlmotor.move_relative(-angy, vely);
        rrmotor.move_relative(angx, velx);
        while (fabs(flmotor.get_target_velocity()) > 0.1) {
            pros::delay(10);
        }
        stop();
    }
    inline void turn_to(double heading, double mult = 0.7) {
        heading = angl_360(heading);
        while (abs(sens::rot-heading) > TURN_MINDIFF) {
            sens::update();
            double rotdiff = angl_180(heading-sens::rot);
            rotdiff = min(1.0, rotdiff/TURN_MAXDIFF);
            turn(rotdiff*GRN_RPM*mult);
        }
    }
    inline void turn_angl(double angle) {
        
    }
}