#ifndef SENSING_H
#define SENSING_H

#include "../globals.hpp"

namespace sens {
    inline double x = 0; inline double y = 0;
    inline double vx = 0; inline double vy = 0;
    inline double ax = 0; inline double ay = 0;
    inline double rot = 0; inline double vrot = 0;
    inline double vrot_corr = 0;
    inline double t0 = 0; inline double t1 = 0;
    inline double dt = 0;
    inline double rot_trg = -1;
    
    inline void reset() {
        inertial.reset();
        while (inertial.is_calibrating()) {}
        x = 0; y = 0;
        vx = 0; vy = 0;
        rot = 0; vrot = 0;
        vrot_corr = 0;
        t0 = 0; t1 = 0;
    }

    inline void update() {
        // position
        t0 = t1;
        t1 = time();
        dt = t1-t0;
        auto [ax, ay, az] = inertial.get_accel();
        x += vx*dt + 0.5*ax*dt*dt; y += vy*dt + 0.5*ay*dt*dt;
        vx += ax*dt*cos(rot); vy += ay*dt*sin(rot);

        // orientation
        rot = inertial.get_heading();
        vrot_corr = 0;
        vrot = inertial.get_gyro_rate().z+vrot_corr;
        vrot_corr = 0;
    }
};

#endif
