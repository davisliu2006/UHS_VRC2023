#pragma once

#include "../globals.hpp"
#include "core.hpp"
#include "../lib/sensing.hpp"

namespace dashboard {
    using namespace display;

    const double delay = 1;
    inline double displ_time = 0;

    // motor temperatures
    inline vector<vector<tuple<pros::Motor, string, int>>> temp_data = {
        {{flmotor, "FL", 0}, {frmotor, "FR", 0}},
        {{rlmotor, "RL", 0}, {rrmotor, "RR", 0}},
        {{flywheel, "Flywheel", 0}, {indexer, "Indxer", 0}},
        {{intake[0], "Intake 1", 0}, {intake[1], "Intake 2", 0}}
    };
    inline void get_temp() {
        for (auto& line: temp_data) {
            for (auto& [mtr, name, temp]: line) {
                temp = mtr.get_temperature();
            }
        }
    }
    inline void displ_temp() {
        display::update();
        pros::screen::set_pen(RGB2COLOR(255, 255, 255));
        for (int i = 0; i < temp_data.size(); i++) {
            auto& line = temp_data[i];
            string txt = "";
            for (int j = 0; j < line.size(); j++) {
                auto& [mtr, name, temp] = line[j];
                txt += name+": "+to_string(temp)+"°C";
                txt += (j == line.size()-1? '\n' : '\t');
            }
            pros::screen::print(pros::E_TEXT_SMALL, 5, 10+i*10, txt.c_str());
        }
    }

    // initialize
    inline void init() {

    }
    
    // update
    inline void update() {
        if (displ_time >= delay) {
            displ_temp();
            displ_time -= delay;
        } else {
            get_temp();
            displ_time += sens::dt;
        }
    }
}