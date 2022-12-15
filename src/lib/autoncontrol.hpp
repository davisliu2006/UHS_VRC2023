#ifndef AUTONCONTROL_H
#define AUTONCONTROL_H

#include "../globals.hpp"
#include "sensing.hpp"

inline vector2 blue_hi(-2.5, -2.5);
inline vector2 red_lo(-1, -1);
inline vector2 red_hi(2.5, 2.5);
inline vector2 blue_lo(1, 1);
inline vector<vector2> rollers = {
    vector2(1.75, -3), vector2(3, -1.75),
    vector2(-3, 1.75), vector2(-1.75, 3)
};
inline vector<vector2> disks = {
    // diangonal
    vector2(-0.5, 0.5), vector2(-1, 1), vector2(-1.5, 1.5),
    vector2(-2, 2), vector2(-2.5, 2.5),
    vector2(0.5, -0.5), vector2(1, -1), vector2(1.5, -1.5),
    vector2(2, -2), vector2(2.5, -2.5),
    // next to diagonal
    vector2(-0.5, 1.5), vector2(0, 1), vector2(-.5, 0.5), /*skip*/ vector2(1.5, -0.5),
    vector2(-1.5, 0.5), /*skip*/ vector2(-0.5, -0.5), vector2(0, -1), vector2(0.5, -1.5),
    // edge
};

namespace auton{
    inline void advance(int left, int right) {
        flmotor.move_velocity(left);
        frmotor.move_velocity(right);
        rlmotor.move_velocity(left);
        rrmotor.move_velocity(right);
    }
    inline void strafe(int front, int rear) {
        flmotor.move_velocity(front);
        frmotor.move_velocity(front);
        rlmotor.move_velocity(rear);
        rrmotor.move_velocity(rear);
    }
    inline void slide(int x, int y) {
        
    }
    inline void rotate(int angle) {

    }
    inline void correct_rot(int target) {
        
    }
}

#endif
