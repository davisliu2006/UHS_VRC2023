#pragma once

#include "../globals.hpp"

namespace sens {
    //positional
    inline double x = 0, y = 0;
    inline double vx = 0, vy = 0;
    inline double ax = 0, ay = 0;

    // rotational
    inline double rot = 0;
    inline double vrot = 0;
    inline double rot_trg = -1; // rotational target

    // timing
    inline double t = 0;
    inline double dt = 0;
    
    // reset
    inline void reset() {
        if ((inertial.get_status() & pros::c::E_IMU_STATUS_ERROR) == pros::c::E_IMU_STATUS_ERROR) {
            pros::lcd::clear_line(0);
            pros::lcd::print(0, "Warning: No inertial attatched.");
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

    // advanced (defined later)
    void update_dynamic_avg();

    // update
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

        // advanced
        // update_dynamic_avg();
    }
};

// ADVANCED

// periodic averages
/*
Measures the average of func() over fixed intervals.
*/
struct periodic_avg {
    double interval = 0;
    double curr_time = 0;
    double val = 0;
    private:
    double _newval = 0;
    public:
    function<double()> func;

    static set<periodic_avg*> instances;

    periodic_avg(double interval1, function<double()> func1) {
        interval = interval1;
        func = func1;
        instances.insert(this);
    }
    ~periodic_avg() {
        instances.erase(this);
    }

    void update() {
        if (curr_time >= interval) {
            val = _newval/curr_time;
            _newval = 0;
            curr_time = 0;
        } else {
            _newval += func()*sens::dt;
            curr_time += sens::dt;
        }
    }

    static void update_all() {
        for (auto* ins: instances) {ins->update();}
    }
};
/*
Measures the average change/time of func() over fixed intervals.
*/
struct periodic_davg {
    double interval = 0;
    double curr_time = 0;
    double val = 0;
    double integral = 0;
    function<double()> func;

    static set<periodic_davg*> instances;

    periodic_davg(double interval1, function<double()> func1) {
        interval = interval1;
        func = func1;
        integral = func();
        instances.insert(this);
    }
    ~periodic_davg() {
        instances.erase(this);
    }

    void update() {
        if (curr_time >= interval) {
            double integral0 = integral;
            integral = func();
            val = (integral-integral0)/curr_time;
            curr_time = 0;
        } else {
            curr_time += sens::dt;
        }
    }

    static void update_all() {
        for (auto* ins: instances) {ins->update();}
    }
};

// sliding averages
/*
Measures the average of func() over the last x seconds.
*/
struct [[deprecated]] sliding_avg {
    
};
/*
Measures the average change/time of func() over the last x seconds.
*/
struct [[deprecated]] sliding_davg {

};

namespace sens {
    // dynamic average update
    inline void update_dynamic_avg() {
        periodic_avg::update_all();
        periodic_davg::update_all();
    }
}