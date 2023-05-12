#pragma once

#include "../globals.hpp"
#include "dashboard.hpp"
#include "selection.hpp"

namespace display {
    inline void init_all() {
        init();
        selection::init();
    }
    inline void on_init() {
        selection::enable();
    }
    inline void on_disable() {
        selection::enable();
    }
    inline void on_opc() {
        selection::disable();
    }
    inline void on_auton() {
        selection::disable();
    }
}