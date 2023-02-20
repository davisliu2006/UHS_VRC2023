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

    // simple move
    #if DRV_MODE == TANK_DRV
    inline void advance(int vel) {
        flmotor.move_velocity(vel);
        frmotor.move_velocity(vel);
        rlmotor.move_velocity(vel);
        rrmotor.move_velocity(vel);
    }
    #endif
    #if DRV_MODE == X_DRV
    inline void slide(int x, int y) {
        flmotor.move_velocity(y+x);
        frmotor.move_velocity(y-x);
        rlmotor.move_velocity(y-x);
        rrmotor.move_velocity(y+x);
    }
    #endif

    // simple turn
    inline void turn(int rotvel) {
        flmotor.move_velocity(rotvel);
        frmotor.move_velocity(-rotvel);
        rlmotor.move_velocity(rotvel);
        rrmotor.move_velocity(-rotvel);
    }

    // stop
    inline void stop() {
        flmotor.move_velocity(0);
        frmotor.move_velocity(0);
        rlmotor.move_velocity(0);
        rrmotor.move_velocity(0);
    }

    // move distance
    #if DRV_MODE == TANK_DRV
    inline void advance_time(double vel, double dt) {
        sens::update();
        advance(vel);
        while (dt > 0) {
            sens::update();
            dt -= sens::dt;
        }
        stop();
    }
    inline void advance_straight(double vel, double dt, double corr = 0) {
        sens::update();
        double rot = sens::rot;
        while (dt > 0) {
            sens::update();
            double rotdiff = angl_180(rot-sens::rot)/TURN_MAXDIFF;
            rotdiff = min(1.0, rotdiff);
            flmotor.move_velocity(vel+rotdiff*corr);
            frmotor.move_velocity(vel-rotdiff*corr);
            rlmotor.move_velocity(vel+rotdiff*corr);
            rrmotor.move_velocity(vel-rotdiff*corr);
            dt -= sens::dt;
        }
        stop();
    }
    inline void advance_dist(double dist, double vel) {
        double ang = dist/WHEEL_C;
        flmotor.move_relative(ang, vel);
        frmotor.move_relative(ang, vel);
        rlmotor.move_relative(ang, vel);
        rrmotor.move_relative(ang, vel);
        while (fabs(flmotor.get_target_velocity()) > 0.1) {
            sens::update();
            // pros::delay(10);
        }
        stop();
    }
    #endif
    #if DRV_MODE == X_DRV
    [[deprecated]] inline void slide_time(int x, int y, double dt) {
        sens::update();
        slide(x, y);
        while (dt > 0) {
            sens::update();
            dt -= sens::dt;
        }
        stop();
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
            sens::update();
            // pros::delay(10);
        }
        stop();
    }
    #endif
    
    // turn angle
    inline void turn_to(double heading, double mult = 0.7) {
        sens::update();
        heading = angl_360(heading);
        while (abs(sens::rot-heading) > TURN_MINDIFF) {
            sens::update();
            double rotdiff = angl_180(heading-sens::rot)/TURN_MAXDIFF;
            rotdiff = min(1.0, rotdiff);
            turn(rotdiff*GRN_RPM*mult);
        }
        stop();
    }
    inline void turn_angl(double angle) {
        sens::update();
        turn_to(angl_360(sens::rot+angle));
    }

    // wait with background processing
    inline void wait(double t) {
        sens::update();
        while (t > 0) {
            sens::update();
            t -= sens::dt;
        }
    }
    inline void wait_until(function<bool()> func) {
        while (!func()) {
            sens::update();
        }
    }

    // intake
    inline void set_intake(int vel) {
        intake.move(vel);
    }
    inline void intake_for(int vel, double dt) {
        set_intake(vel);
        wait(dt);
        set_intake(0);
    }

    // shooter
    inline void shoot(int n = 1) {
        flywheel.move(MTR_MAX);
        while (n-- > 0) {
            indexer.move(-MTR_MAX);
            wait(2);
            indexer.move(0);
            wait_until([]() {
                return flywheel.get_actual_velocities()[0] >= BLU_RPM*0.9;
            });
            indexer.move(MTR_MAX);
            wait(2);
            indexer.move(-MTR_MAX);
            wait(2);
            indexer.move(0);
        }
        flywheel.move(0);
    }
}
