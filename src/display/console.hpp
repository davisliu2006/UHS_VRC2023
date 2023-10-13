#pragma once

#include "../globals.hpp"
#include "core.hpp"

namespace [[deprecated]] console {
    using namespace display;

    // function declarations
    void init(); void update();

    // data and labels
    const int BUF_MAX = 10;
    inline deque<string> data;
    inline Label* lbl = new Label("", 5, 10, pros::E_TEXT_SMALL);
    inline GUILayer layer;

    // print
    inline void print(const string& str) {
        for (const char& c: str) {
            if (c == '\n') {
                while (data.size() >= BUF_MAX) {data.pop_front();}
                data.push_back("");
                update();
            } else {
                data.back().push_back(c);
            }
        }
    }

    // initialize
    inline void init() {
        layer.labels = {lbl};
    }

    // enable and disable
    inline void enable() {
        layer.enabled = true;
        update();
    }
    inline void disable() {
        layer.enabled = false;
        update();
    }

    // update
    inline void update() {
        string str;
        for (const string& line: data) {
            str += line;
        }
        lbl->text = str;
        display::update();
    }

    // ostream
    struct OStream {
        OStream& operator <<(int32_t x) {
            print(to_string(x));
            return *this;
        }
        OStream& operator <<(int64_t x) {
            print(to_string(x));
            return *this;
        }
        OStream& operator <<(char x) {
            print(string()+x);
            return *this;
        }
        OStream& operator <<(double x) {
            print(to_string(x));
            return *this;
        }
        OStream& operator <<(const string& obj) {
            print(obj);
            return *this;
        }
    };
    inline OStream out;
}