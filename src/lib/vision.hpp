#pragma once

#include "../globals.hpp"
#include "autonomous.hpp"
#include "../display/selection.hpp"

namespace [[deprecated]] vision {/*
    Range factor for sensor. 
    Change lower if detects too much background color
    Change higher if detects too little of the goal 
    */
    const double BLUE_RANGE_FACTOR = 3.800; //Change range factor for blue
    const double RED_RANGE_FACTOR = 3.800; //Change range factor for red
    const double HORIZONTAL_ERROR_ROOM = 4; //Change higher if too slow and change lower if not accurate enough
    const double VERTICIAL_ERROR_ROOM = 4; //Change higher if too slow and change lower if not accurate enough
    inline int objects = 0;

    //Initalize the vision sensor
    inline pros::Vision vsensor(21);

    //Uhhhh like set signature for the vision sensor idfk
    inline pros::vision_signature_s_t BLUE = pros::Vision::signature_from_utility(1, -4293, -3397, -3846, 7555, 10683, 9118, BLUE_RANGE_FACTOR, 0);
    inline pros::vision_signature_s_t RED = pros::Vision::signature_from_utility(2, 10357, 11637, 10997, -1525, -1035, -1280, RED_RANGE_FACTOR, 1);

    /*
    Set up code for the vision sensor.
    */
    inline void init() {
        
    }
    inline void vision_shoot() {
        //Adds the red and blue colors to the sensor
        vsensor.set_signature(0, &BLUE);
        vsensor.set_signature(1, &RED);
        objects = vsensor.get_object_count();
        pros::vision_object_s_t goal;
        if (objects >= 1) {
            if (selection::alliance == TEAM_RED) {
                goal = vsensor.get_by_sig(0, RED.id);
            } else if (selection::alliance == TEAM_BLUE) {
                goal = vsensor.get_by_sig(0, RED.id);
            }
        }
        while (goal.x_middle_coord < -HORIZONTAL_ERROR_ROOM || goal.x_middle_coord > HORIZONTAL_ERROR_ROOM || goal.y_middle_coord < -VERTICIAL_ERROR_ROOM || goal.y_middle_coord > VERTICIAL_ERROR_ROOM) {
            while (goal.x_middle_coord < -HORIZONTAL_ERROR_ROOM || goal.x_middle_coord > HORIZONTAL_ERROR_ROOM) {
                if (goal.x_middle_coord < -HORIZONTAL_ERROR_ROOM) {
                    auton::turn(60);
                }
                if (goal.x_middle_coord > HORIZONTAL_ERROR_ROOM) {
                    auton::turn(-60);
                }
            }
            while (goal.y_middle_coord < -VERTICIAL_ERROR_ROOM || goal.y_middle_coord > VERTICIAL_ERROR_ROOM) {
                if (goal.y_middle_coord < -VERTICIAL_ERROR_ROOM) {
                    auton::advance(70);
                }
                if (goal.y_middle_coord > VERTICIAL_ERROR_ROOM) {
                    auton::advance(-70);
                }
            }
        }
    }
}