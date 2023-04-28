#pragma once

#include "../globals.hpp"
#include "sensing.hpp"

namespace display {
    const double delay = 1;
    inline double displ_time = 0;

    // motor temperatures
    inline vector<vector<tuple<pros::Motor, const char*, int>>> temp_data = {
        {{flmotor, "FL", 0}, {frmotor, "FR", 0}},
        {{rlmotor, "RL", 0}, {rrmotor, "RR", 0}},
        {{flywheel, "Flywheel", 0}, {indexer, "Indxer", 0}},
        //{{intake[0], "Intake 1", 0}, {intake[1], "Intake 2", 0}}
    };
    inline void displ_temp() {
        if (displ_time >= delay) {
            for (int i = 0; i < temp_data.size(); i++) {
                auto& line = temp_data[i];
                pros::lcd::clear_line(i+1);
                for (int j = 0; j < line.size(); j++) {
                    auto& [mtr, name, temp] = line[j];
                    pros::lcd::print(i+1, "%s: %.2f%c", name, temp,
                        (j == line.size()-1? '\n' : '\t'));
                }
            }
            displ_time = 0;
        } else {
            for (auto& line: temp_data) {
                for (auto& [mtr, name, temp]: line) {
                    temp = mtr.get_temperature();
                }
            }
            displ_time += sens::dt;
        }
    }

    // udpate
    inline void update() {
        displ_temp();
    }
}