#ifndef ROUTE_H
#define ROUTE_H

#include "../globals.hpp"
#include "../lib/autonomous.hpp"

inline void route_1() {
    /*auton::turn_to(0);
    pros::delay(100);
    auton::turn_to(90);
    pros::delay(100);
    auton::turn_to(180);
    pros::delay(100);
    auton::turn_to(45);
    pros::delay(100);
    auton::turn_to(0);
    pros::delay(100);*/
    // changing this to lower speed cuz it might help
    while (true) {
        // now it goes back and forth forever
        auton::slide_dist(TILE*5, 0, 150);
        pros::delay(500);
        auton::slide_dist(TILE*5, 180, 150);
        pros::delay(500);
    }
}

#endif