#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"

inline void route_1() {
    #if DRV_MODE == TANK_DRV
    
    #elif DRV_MODE == X_DRV
    while (true) {
        // now it goes back and forth forever
        auton::slide_dist(TILE, 0, 150);
        pros::delay(500);
        auton::slide_dist(TILE, 180, 150);
        pros::delay(500);
    }
    #endif
}

inline void route_2() {
    
}