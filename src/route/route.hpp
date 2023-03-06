#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"
#include "skills.hpp"

namespace route {
    inline void route1() {
        #if DRV_MODE == TANK_DRV
        auton::set_intake(-200); // spin roller
        auton::advance_straight(-WHEEL_RPM, 0.75);
        auton::set_intake(0);
        
        #elif DRV_MODE == X_DRV
        while (true) {
            auton::slide_dist(TILE, 0, 150);
            auton::wait(0.5);
            auton::slide_dist(TILE, 180, 150);
            auton::wait(0.5);
        }
        #endif
    }

    inline void route2() {
        #if DRV_MODE == TANK_DRV
        auton::advance_straight(WHEEL_RPM, 1); // go to roller
        auton::turn_angl(90);
        auton::advance_straight(WHEEL_RPM, 1);
        auton::turn_angl(-90);
        auton::set_intake(100); // spin roller
        auton::advance_straight(-WHEEL_RPM, 1);
        auton::set_intake(0);
        #elif DRV_MODE == X_DRV
        while (true) {
            auton::slide_dist(TILE, 0, 150);
            auton::wait(0.5);
            auton::slide_dist(TILE, 180, 150);
            auton::wait(0.5);
        }
        #endif
    }
}