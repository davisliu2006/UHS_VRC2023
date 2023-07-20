#pragma once

#include "../include/main.h"
#include "../globals.hpp"
#include "../lib/autonomous.hpp"

namespace route {
    // SUBROUTES
    
    inline void autonPIDTest() {
        auton::vector center = {};
        // auton::moveDistance(8, 2000, &center);
        // auton::moveDistance(6, -2000, &center);
    }

    inline void spin_roller() {
        auton::set_intake(-INTK_RPM);
        auton::advance_time(-WHEEL_RPM*0.3, 0.4);
        auton::set_intake(0);
        auton::advance_time(WHEEL_RPM, 0.2);
    }

    inline void spin_roller_far() {
        auton::set_intake(-INTK_RPM);
        auton::advance_time(-WHEEL_RPM*0.3, 0.6);
        auton::set_intake(0);
        auton::advance_time(WHEEL_RPM, 0.2);
    }

    inline void get_disks() {
        // turn to intake other 3 disk
        auton::turn_to(225);
        //move towards other 3 disks
        auton::set_intake(200);
        auton::advance_time(-WHEEL_RPM, 2.53);
        auton::advance_time(WHEEL_RPM, 0.5);
        // shoot
        auton::turn_to(135);
        auton::shoot(BLU_RPM*0.9, 0.95, 3, 3);
    }

    // ROUTES

    inline void close_hi() {
        #if DRV_MODE == TANK_DRV
        auton::set_flywheel(BLU_RPM*0.9); // pre-accelerate
        // spin roller
        spin_roller();
        // set up shoot
        auton::turn_to(45);
        auton::advance_time(WHEEL_RPM, 2);
        auton::turn_to(-45);
        // shoot
        auton::shoot(BLU_RPM*0.9, 0.95, 3, 2);
        #elif DRV_MODE == X_DRV
        #endif  
    }

    inline void far_hi() {
        #if DRV_MODE == TANK_DRV
        auton::set_flywheel(BLU_RPM*0.9); // pre-accelerate
        // go to roller
        auton::advance_time(-WHEEL_RPM, 0.8);
        auton::turn_to(90);
        // spin roller
        spin_roller_far();
        // set up shoot
        auton::turn_to(45);
        auton::advance_time(WHEEL_RPM, 2);
        auton::turn_to(135);
        // shoot
        auton::shoot(BLU_RPM*0.9, 0.95, 3, 2);
        // get_disks();
        #elif DRV_MODE == X_DRV
        #endif
    }

    inline void close_lo() {
        #if DRV_MODE == TANK_DRV
        auton::set_flywheel(BLU_RPM*0.9); // pre-accelerate
        // spin roller
        spin_roller();
        // set up shoot
        auton::turn_to(90);
        auton::advance_time(WHEEL_RPM, 1);
        // shoot
        auton::shoot(BLU_RPM*0.9, 0.95, 3, 2);
        #elif DRV_MODE == X_DRV
        #endif
    }

    inline void far_lo() {
        #if DRV_MODE == TANK_DRV
        auton::set_flywheel(BLU_RPM*0.9); // pre-accelerate
        // go to roller
        auton::advance_time(-WHEEL_RPM, 0.8);
        auton::turn_to(90);
        // spin roller
        spin_roller();
        // set up shoot
        auton::turn_to(0);
        auton::advance_time(WHEEL_RPM, 1);
        // shoot
        auton::shoot(BLU_RPM*0.9, 0.95, 3, 2);
        get_disks();
        #elif DRV_MODE == X_DRV
        #endif
    }

    inline void test() {
        auton::set_flywheel(BLU_RPM*0.9); // pre-accelerate
        auton::wait(1);
        auton::shoot(BLU_RPM*0.9, 0.95, 3, 2);
    }

    // SKILLS ROUTE

    inline void skills() {
        
    }
}