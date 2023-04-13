#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"
#include "skills.hpp"

namespace route {
    inline void route1() {
        #if DRV_MODE == TANK_DRV
        auton::set_intake(-INTK_RPM); // spin roller
        auton::advance_straight(-WHEEL_RPM*0.5, 0.5);
        auton::set_intake(0);
        auton::turn_angl(90); // set up shoot
        auton::set_indexer(true); // shoot
        auton::wait(1);
        auton::set_indexer(false);
        auton::wait(1);
        auton::set_indexer(true);
        auton::wait(1);
        auton::set_indexer(false);
        
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
        auton::advance_time(-WHEEL_RPM, 0.8); // go to roller
        auton::turn_to(90);
        auton::set_intake(-INTK_RPM); // spin roller
        auton::advance_time(-WHEEL_RPM*0.5, 0.5);
        auton::set_intake(0);
        auton::set_flywheel(BLU_RPM); // set up shoot
        auton::turn_to(0);
        auton::advance_time(WHEEL_RPM, 1);
        auton::wait(3);
        auton::set_indexer(true); // shoot
        auton::wait(3);
        auton::set_indexer(false);
        auton::wait(3);
        auton::set_indexer(true);
        auton::wait(3);
        auton::set_indexer(false);

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