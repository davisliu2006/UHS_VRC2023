#pragma once

#include "../globals.hpp"

namespace sens {
    //positional
    inline double x = 0; inline double y = 0;
    inline double vx = 0; inline double vy = 0;
    inline double ax = 0; inline double ay = 0;

    // rotational
    inline double rot = 0;
    inline double vrot = 0;
    inline double rot_trg = -1; // rotational target

    // timing
    inline double t = 0;
    inline double dt = 0;
    
    inline void reset() {
        if ((inertial.get_status() & pros::c::E_IMU_STATUS_ERROR) == pros::c::E_IMU_STATUS_ERROR) {
            pros::lcd::print(1, "Warning: No inertial attatched.");
            return;
        }
        inertial.reset();
        while (inertial.is_calibrating()) {}
        x = 0; y = 0;
        vx = 0; vy = 0;
        rot = 0; vrot = 0;
        rot_trg = -1;
        t = time(); // IMPORTANT: timer does not reset
    }

    inline void update() {
        // timing
        double t0 = t;
        t = time();
        dt = t-t0;

        // position
        auto [ax, ay, az] = inertial.get_accel();
        x += vx*dt + 0.5*ax*dt*dt; y += vy*dt + 0.5*ay*dt*dt;
        vx += ax*dt*cos(rot); vy += ay*dt*sin(rot);

        // orientation
        rot = inertial.get_heading();
        vrot = inertial.get_gyro_rate().z;
    }
};