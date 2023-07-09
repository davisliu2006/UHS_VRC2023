#pragma once

#include "../globals.hpp"

namespace display {
    const int SX = 480;
    const int SY = 272;

    // button
    struct Button {
        static const uint32_t DEF_CLR = RGB2COLOR(150, 150, 150);

        int x, y;
        int sx, sy;
        uint32_t color = DEF_CLR;
        string text;
        function<void(Button*)> on_press;

        Button(const string& text1, int x1, int y1, int sx1, int sy1,
        const function<void(Button*)>& func) {
            text = text1;
            x = x1; y = y1;
            sx = sx1; sy = sy1;
            on_press = func;
        }
        ~Button() {}

        void draw() {
            pros::screen::set_pen(color);
            pros::screen::draw_rect(x-sx/2, y-sy/2, x+sx/2, y+sy/2);
            pros::screen::print(pros::E_TEXT_MEDIUM, x-sx/2+1, y, text.c_str());
        }
    };

    // label
    struct Label {
        int x, y;
        pros::text_format_e_t style;
        string text;

        Label(const string& text1, int x1, int y1, pros::text_format_e_t style1) {
            text = text1;
            x = x1;
            y = y1;
            style = style1;
        }

        void draw() {
            pros::screen::print(style, x, y, text.c_str());
        }
    };

    // gui layer
    struct GUILayer {
        static inline set<GUILayer*> instances;

        bool enabled = false;
        set<Button*> buttons;
        set<Label*> labels;

        GUILayer() {
            instances.insert(this);
        }
        ~GUILayer() {
            instances.erase(this);
        }
        
        void draw() {
            for (Button* btn: buttons) {btn->draw();}
            for (Label* lbl: labels) {lbl->draw();}
        }
        void on_press(int x, int y) {
            for (Button* btn: buttons) {
                if (in_range(x, btn->x-btn->sx/2, btn->x+btn->sx/2)
                && in_range(y, btn->y-btn->sy/2, btn->y+btn->sy/2)) {
                    btn->on_press(btn);
                }
            }
        }

        static void draw_all() {
            for (GUILayer* layer: instances) {
                if (layer->enabled) {layer->draw();}
            }
        }
        static void check_all(int x, int y) {
            for (GUILayer* layer: instances) {
                if (layer->enabled) {layer->on_press(x, y);}
            }
        }
    };

    inline void on_press() {
        auto status = pros::screen::touch_status();
        auto& x = status.x;
        auto& y = status.y;
        GUILayer::check_all(x, y);
    }

    inline void init() {
        pros::screen::touch_callback(on_press, pros::E_TOUCH_PRESSED);
    }
    
    inline void update() {
        pros::screen::set_eraser(RGB2COLOR(0, 0, 0));
        pros::screen::erase();
        GUILayer::draw_all();
    }
}