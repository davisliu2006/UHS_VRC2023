#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"

namespace route {
    // SUBROUTES

    inline void spin_roller() {
        auton::set_intake(-INTK_RPM);
        auton::advance_time(-WHEEL_RPM*0.3, 0.5);
        auton::set_intake(0);
    }

    // ROUTES

    inline void close_hi() {
        #if DRV_MODE == TANK_DRV
        auton::set_flywheel(BLU_RPM); // pre-accelerate
        // spin roller
        spin_roller();
        // set up shoot
        auton::turn_to(90);
        // shoot
        auton::shoot(BLU_RPM, 2);
        #elif DRV_MODE == X_DRV
        #endif  
    }

    inline void far_hi() {
        #if DRV_MODE == TANK_DRV
        auton::set_flywheel(BLU_RPM); // pre-accelerate
        // go to roller
        auton::advance_time(-WHEEL_RPM, 0.8);
        auton::turn_to(90);
        // spin roller
        spin_roller();
        // set up shoot
        auton::advance_time(WHEEL_RPM, 1);
        // shoot
        auton::shoot(BLU_RPM, 2);
        #elif DRV_MODE == X_DRV
        #endif
    }

    inline void close_lo() { // incomplete
        #if DRV_MODE == TANK_DRV
        auton::set_flywheel(BLU_RPM); // pre-accelerate
        spin_roller();
        #elif DRV_MODE == X_DRV
        #endif
    }

    inline void far_lo() {
        #if DRV_MODE == TANK_DRV
        auton::set_flywheel(BLU_RPM); // pre-accelerate
        // go to roller
        auton::advance_time(-WHEEL_RPM, 0.8);
        auton::turn_to(90);
        // spin roller
        spin_roller();
        // set up shoot
        auton::turn_to(0);
        auton::advance_time(WHEEL_RPM, 1);
        // shoot
        auton::shoot(BLU_RPM, 2);
        #elif DRV_MODE == X_DRV
        #endif
    }

    // SKILLS ROUTE

    inline void skills() {
        
    }
}