#pragma once

#include "../globals.hpp"
#include "core.hpp"

namespace console {
    using namespace display;

    // function declarations
    void init(); void update();

    // data
    const int BUF_MAX = 10;
    inline deque<string> data;

    // print
    inline void print(const string& str) {
        for (const char& c: str) {
            if (c == '\n') {
                while (data.size() >= BUF_MAX) {data.pop_front();}
                data.push_back("");
            } else {
                data.back().push_back(c);
            }
        }
    }

    // initialize
    inline void init() {

    }

    // enable and disable
    inline void enable() {
        update();
    }
    inline void disable() {
        update();
    }

    // update
    inline void update() {
        display::update();
        int line = 0;
        for (const string& str: data) {
            pros::screen::print(pros::E_TEXT_MEDIUM, 5, 5+line*5, str.c_str());
        }
    }
}