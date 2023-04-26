#pragma once

#include "../globals.hpp"
#include "sensing.hpp"

// probably useless definitions
inline vector2 blue_hi = {-2.5, -2.5};
inline vector2 red_lo = {-1, -1};
inline vector2 red_hi = {2.5, 2.5};
inline vector2 blue_lo = {1, 1};
inline vector<vector2> rollers = {
    {1.75, -3}, {3, -1.75},
    {-3, 1.75}, {-1.75, 3}
};
inline vector<vector2> disks = {
    // diangonal
    {-0.5, 0.5}, {-1, 1}, {-1.5, 1.5}, {-2, 2}, {-2.5, 2.5},
    {0.5, -0.5}, {1, -1}, {1.5, -1.5}, {2, -2}, {2.5, -2.5},
    // next to diagonal
    {-0.5, 1.5}, {0, 1}, {-.5, 0.5}, /*skip*/ {1.5, -0.5},
    {-1.5, 0.5}, /*skip*/ {-0.5, -0.5}, {0, -1}, {0.5, -1.5},
    // edge
};

namespace auton {
    const double TURN_MINDIFF = 5; // changes turn tolerence (minimum angle diff)
    const double TURN_MAXDIFF = 100; // changes turn scaling upper bound angle

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

    // wait with background processing
    inline void wait(double dt) {
        sens::update();
        while (dt > 0) {
            sens::update();
            dt -= sens::dt;
        }
    }
    inline void wait_until(function<bool()> func) {
        sens::update();
        while (!func()) {
            sens::update();
        }
    }

    // move distance
    #if DRV_MODE == TANK_DRV
    inline void advance_time(double vel, double dt) {
        advance(vel);
        wait(dt);
        stop();
    }
    inline void advance_straight(double vel, double dt, double corr = 1) {
        sens::update();
        double rot = sens::rot;
        while (dt > 0) {
            sens::update();
            double rotdiff = angl_180(rot-sens::rot)/TURN_MAXDIFF;
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
        while (abs(flmotor.get_target_velocity()) > 1) {
            sens::update();
        }
        stop();
    }
    #endif
    #if DRV_MODE == X_DRV
    [[deprecated]] inline void slide_time(double x, double y, double dt) {
        sens::update();
        slide(x, y);
        while (dt > 0) {
            sens::update();
            dt -= sens::dt;
        }
        stop();
    }
    [[deprecated]] inline void slide_dist(double dist, double ang, double vel) { // inches
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
        while (abs(flmotor.get_target_velocity()) > 1) {
            sens::update();
        }
        stop();
    }
    #endif
    
    // turn angle
    #define TURN_IMPL 1
    #if TURN_IMPL == 1 // ROT_MINDIFF only changes tolerance, does not change scaling
    inline void turn_to(double heading, double mult = 1) {
        sens::update();
        heading = angl_360(heading);
        while (abs(sens::rot-heading) > TURN_MINDIFF) {
            sens::update();
            double rotdiff = angl_180(heading-sens::rot)/TURN_MAXDIFF;
            rotdiff = min(1.0, rotdiff);
            turn(rotdiff*WHEEL_RPM*mult);
        }
        stop();
    }
    #elif TURN_IMPL == 2 // ROT_MINDIFF changes scaling and tolerance
    inline void turn_to(double heading, double mult = 1) {
        sens::update();
        heading = angl_360(heading);
        double rotdiff_raw;
        while ((rotdiff_raw = abs(angl_180(heading-sens::rot))) > TURN_MINDIFF) {
            sens::update();
            double rotdiff = (rotdiff_raw-sign(rotdiff_raw)*TURN_MINDIFF*0.5)
                /(TURN_MAXDIFF-TURN_MINDIFF*0.5);
            rotdiff = min(1.0, rotdiff);
            turn(rotdiff*WHEEL_RPM*mult);
        }
        stop();
    }
    #endif
    inline void turn_angl(double angle) {
        sens::update();
        turn_to(angl_360(sens::rot+angle));
    }

    // intake
    inline void set_intake(int vel) {
        intake.move_velocity(vel);
    }
    inline void intake_for(int vel, double dt) {
        set_intake(vel);
        wait(dt);
        set_intake(0);
    }

    // shooter
    /*
    val = true --> forward
    val = false --> rest
    */
    #if INDEXER_TYPE == TYPE_MTR
    inline void set_indexer(bool val) {
        if (val) {
            indexer.move_absolute(60, INDX_RPM*0.8);
        } else {
            indexer.move_absolute(5, INDX_RPM*0.8);
        }
    }
    #elif INDEXER_TYPE == TYPE_PNEU
    inline void set_indexer(bool val) {
        indexer.set_value(pos*ADI_MAX);
    }
    #endif
    inline void set_flywheel(int vel) {
        if (vel == 0) { // no braking for flywheel
            flywheel.move(0);
        } else {
            flywheel.move_velocity(vel);
        }
    }
    inline void shoot(int vel, double min_pct, const double max_wait, int n = 1) {
        set_flywheel(vel);
        set_indexer(false);
        while (n-- > 0) {
            double wt = max_wait;
            wait(2); wt -= 2;
            wait_until([&]() {
                return flywheel.get_actual_velocity() >= vel*min_pct
                    || (wt -= sens::dt) <= 0;
            });
            set_flywheel(vel);
            auton::wait(0.2);
            set_indexer(true);
            wait(1);
            set_indexer(false);
        }
        set_flywheel(0);
    }

    // initialize
    inline bool did_init = false;
    inline bool need_sensreset = false;
    /*
    Runs at the beginning of autonomous before any route.
    For any initializations that cannot occur during initialize().
    */
    inline void init() {
        did_init = true;
        // sensing
        if (need_sensreset && pros::competition::is_autonomous()) {
            sens::reset();
        }
        need_sensreset = false;
        // indexer
        #if INDEXER_TYPE == TYPE_MTR
        indexer.move(-MTR_MAX);
        wait(0.2);
        indexer.move(0);
        indexer.tare_position();
        indexer.move_absolute(5, INDX_RPM);
        #endif
    }
}