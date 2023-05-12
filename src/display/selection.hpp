#pragma once

#include "../globals.hpp"
#include "core.hpp"

enum alliance_e {TEAM_RED, TEAM_BLUE};

namespace selection {
    using namespace display;

    // function declarations
    void btnpress(Button* btn);
    void init(); void update();

    // route selection
    inline int route = 1;
    inline vector<Button*> buttons = {
        new Button("Skills", SX*0.25, SY*0.1, SX*0.5, SY*0.2, btnpress),
        new Button("Auton 1", SX*0.125, SY*0.3, SX*0.25, SY*0.2, btnpress),
        new Button("Auton 2", SX*0.375, SY*0.3, SX*0.25, SY*0.2, btnpress),
        new Button("Auton 3", SX*0.625, SY*0.3, SX*0.25, SY*0.2, btnpress),
        new Button("Auton 4", SX*0.125, SY*0.5, SX*0.25, SY*0.2, btnpress),
        new Button("Auton 5", SX*0.375, SY*0.5, SX*0.25, SY*0.2, btnpress),
        new Button("Auton 6", SX*0.625, SY*0.5, SX*0.25, SY*0.2, btnpress)
    };
    inline void btnpress(Button* btn) {
        for (int i = 0; i < buttons.size(); i++) {
            if (buttons[i] == btn) {route = i; break;}
        }
        update();
    }
    inline GUILayer route_select;

    // alliance selection
    inline int alliance = TEAM_RED;
    inline Button* redbtn = new Button("Red", SX*0.125, SY*0.7, SX*0.25, SY*0.2, [](Button* btn) {
        alliance = TEAM_RED;
        update();
    });
    inline Button* bluebtn = new Button("Blue", SX*0.375, SY*0.7, SX*0.25, SY*0.2, [](Button* btn) {
        alliance = TEAM_BLUE;
        update();
    });
    inline GUILayer alliance_select;

    // intialize
    inline void init() {
        route_select.buttons = set<Button*>(buttons.begin(), buttons.end());
        alliance_select.buttons = {redbtn, bluebtn};
    }

    // enable and disable
    inline void enable() {
        route_select.enabled = true;
        alliance_select.enabled = true;
        update();
    }
    inline void disable() {
        route_select.enabled = false;
        alliance_select.enabled = false;
        update();
    }

    // update
    inline void update() {
        // route buttons
        for (int i = 0; i < buttons.size(); i++) {
            buttons[i]->color = (route == i? RGB2COLOR(200, 150, 200)
                : Button::DEF_CLR);
        }
        // alliance buttons
        redbtn->color = (alliance == TEAM_RED && route > 0? RGB2COLOR(200, 150, 150)
            : Button::DEF_CLR);
        bluebtn->color = (alliance == TEAM_BLUE && route > 0? RGB2COLOR(150, 150, 200)
            : Button::DEF_CLR);
        display::update();
    }
}